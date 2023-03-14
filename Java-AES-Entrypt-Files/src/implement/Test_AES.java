//package implement;
//
//public class Test_AES {
//
//    private static int Nb = 4;
//    private static int Nk = 2; //CipherKey.length
//    private static int Nr = Nk + 6;
//
//
//    /**
//     * 仿射变换
//     * @param b
//     * @param sign  C：加密  D：解密
//     * @return
//     */
//    static byte AffineTransformation(byte b, char sign) {
//        byte[] x = Integer.toBinaryString((b & 0xff) + 0x100).substring(1).getBytes();
//        for (int i = 0; i < x.length; i++) x[i] -= '0';
//        if (sign == 'C') {
//            byte[] x_ = new byte[8];
//            byte b_ = 0;
//            for (int i = 0; i < 8; i++) {
//                x_[i] = (byte) (x[i] ^ x[(i + 1) % 8] ^ x[(i + 2) % 8] ^ x[(i + 3) % 8] ^ x[(i + 4) % 8]);
//                b_ += x_[i] * Math.pow(2, 7 - i);
//            }
//            return (byte) (b_ ^ 0x63);
//        } else {
//            byte[] x_ = new byte[8];
//            byte b_ = 0;
//            for (int i = 0; i < 8; i++) {
//                x_[i] = (byte) (x[(i + 1) % 8] ^ x[(i + 3) % 8] ^ x[(i + 6) % 8]);
//                b_ += x_[i] * Math.pow(2, 7 - i);
//            }
//            return (byte) (b_ ^ 0x05);
//        }
//    }
//
//    /**
//     * 加密密钥扩展
//     * @param CipherKey
//     * @return
//     */
//    static Word[][] KeyExpansion(Word[] CipherKey) {
//        Word[] W = new Word[Nb * (Nr + 1)];
//        //密钥扩展
//        Word Temp;
//        if (Nk <= 6) {
//            for (int i = 0; i < Nk; i++)
//                W[i] = CipherKey[i];
//            for (int i = Nk; i < W.length; i++) {
//                Temp = new Word(W[i - 1]);
//                if (i % Nk ==0)
//                    Temp = Word.add(SubByte(Rotl(Temp)), Rcon(i / Nk));
//                W[i] = Word.add(W[i - Nk], Temp);
//            }
//        } else {
//            for (int i = 0; i < Nk; i++)
//                W[i] = CipherKey[i];
//            for (int i = Nk; i < W.length; i++) {
//                Temp = new Word(W[i - 1]);
//                if (i % Nk ==0)
//                    Temp = Word.add(SubByte(Rotl(Temp)), Rcon(i / Nk));
//                else if (i % Nk == 4)
//                    Temp = SubByte(Temp);
//                W[i] = Word.add(W[i - Nk], Temp);
//            }
//        }
//        //轮密钥选择
//        Word[][] RoundKey = new Word[Nr + 1][Nb];
//        for (int i = 0; i < Nr + 1; i++)
//            for (int j = 0; j < Nb; j++)
//                RoundKey[i][j] = W[Nb * i + j];
//        return RoundKey;
//    }
//
//    static Word SubByte(Word a) {
//        Word w = new Word(a);
//        for (int i = 0; i < 4; i++) {
//            //乘法逆代替
//            w.word[i] = Word.inverse(w.word[i]);
//            //仿射变换
//            w.word[i] = AffineTransformation(w.word[i], 'C');
//        }
//        return w;
//    }
//
//    static Word Rotl(Word a) {
//        Word w = new Word(a);
//        byte b = w.word[0];
//        for (int i = 0; i < 3; i++)
//            w.word[i] = w.word[i + 1];
//        w.word[3] = b;
//        return w;
//    }
//
//    static Word Rcon(int n) {
//        Word Rcon = new Word(new byte[4]);
//        byte RC = 1;
//        for (int i = 1; i < n; i++)
//            RC = Word.xtime(RC);
//        Rcon.word[0] = RC;
//        return Rcon;
//    }
//
//    /**
//     * 解密密钥扩展
//     * @param CipherKey
//     * @return
//     */
//    static Word[][] InvKeyExpansion(Word[] CipherKey) {
//        Word[][] InvRoundKey = KeyExpansion(CipherKey);
//        for (int i = 1; i < Nr; i++)
//            InvRoundKey[i] = InvMixColumn(InvRoundKey[i]);
//        return InvRoundKey;
//    }
//
//    /**
//     * S盒变换
//     * @param state
//     * @return
//     */
//    static Word[] ByteSub(Word[] state) {
//        for (int i = 0; i < Nb; i++)
//            for (int j = 0; j < 4; j++) {
//                //乘法逆代替
//                state[i].word[j] = Word.inverse(state[i].word[j]);
//                //仿射变换
//                state[i].word[j] = AffineTransformation(state[i].word[j], 'C');
//            }
//        return state;
//    }
//
//    /**
//     * S盒逆变换
//     * @param state
//     * @return
//     */
//    static Word[] InvByteSub(Word[] state) {
//        for (int i = 0; i < Nb; i++)
//            for (int j = 0; j < 4; j++) {
//                //仿射变换
//                state[i].word[j] = AffineTransformation(state[i].word[j], 'D');
//                //乘法逆代替
//                state[i].word[j] = Word.inverse(state[i].word[j]);
//            }
//        return state;
//    }
//
//    /**
//     * 行移位变换
//     * @param state
//     * @return
//     */
//    static Word[] ShiftRow(Word[] state) {
//        byte[][] b = new byte[4][Nb];
//        for (int j = 0; j < Nb; j++)
//            for (int i = 0; i < 4; i++)
//                b[i][j] = state[j].word[i];
//        for (int i = 1; i < 4; i++)
//            for (int k = 0; k < i; k++) {
//                byte t = b[i][0];
//                for (int j = 0; j < Nb - 1; j++)
//                    b[i][j] = b[i][j + 1];
//                b[i][Nb - 1] = t;
//            }
//        for (int j = 0; j < Nb; j++)
//            for (int i = 0; i < 4; i++)
//                state[j].word[i] = b[i][j];
//        return state;
//    }
//
//    /**
//     * 行移位逆变换
//     * @param state
//     * @return
//     */
//    static Word[] InvShiftRow(Word[] state) {
//        byte[][] b = new byte[4][Nb];
//        for (int j = 0; j < Nb; j++)
//            for (int i = 0; i < 4; i++)
//                b[i][j] = state[j].word[i];
//        for (int i = 1; i < 4; i++)
//            for (int k = 0; k < Nb - i; k++) {
//                byte t = b[i][0];
//                for (int j = 0; j < Nb - 1; j++)
//                    b[i][j] = b[i][j + 1];
//                b[i][Nb - 1] = t;
//            }
//        for (int j = 0; j < Nb; j++)
//            for (int i = 0; i < 4; i++)
//                state[j].word[i] = b[i][j];
//        return state;
//    }
//
//    /**
//     * 列混合变换
//     * @param state
//     * @return
//     */
//    static Word[] MixColumn(Word[] state) {
//        byte[] b = {(byte) 0x02, (byte) 0x01, (byte) 0x01, (byte) 0x03};
//        Word a = new Word(b);
//        for (int i = 0; i < Nb; i++)
//            state[i] = Word.multiply(a, state[i]);
//        return state;
//    }
//    /**
//     * 列混合逆变换
//     * @param state
//     * @return
//     */
//    static Word[] InvMixColumn(Word[] state) {
//        byte[] b = {(byte) 0x0E, (byte) 0x09, (byte) 0x0D, (byte) 0x0B};
//        Word a = new Word(b);
//        for (int i = 0; i < Nb; i++)
//            state[i] = Word.multiply(a, state[i]);
//        return state;
//    }
//
//    /**
//     * 轮密钥加变换
//     * @param state
//     * @param key
//     * @return
//     */
//    static Word[] AddRoundKey(Word[] state, Word[] key) {
//        for (int i = 0; i < Nb; i++)
//            state[i] = Word.add(state[i], key[i]);
//        return state;
//    }
//
//    /**
//     * 加密
//     * @param plaintext  4个字长度的明文
//     * @param CipherKey  4、6或8个字长度的密钥
//     * @return
//     */
//    public static Word[] encrypt(Word[] plaintext, Word[] CipherKey) {
//        Nb = 4;
//        Nk = CipherKey.length;
//        Nr = Nk + 6;
//
//        //加密密钥扩展
//        RoundKey = KeyExpansion(CipherKey);
//        Word[] ciphertext = new Word[plaintext.length];
//        for (int i = 0; i < plaintext.length; i++)
//            ciphertext[i] = new Word(plaintext[i]);
//        //初始轮密钥加
//        ciphertext = AddRoundKey(ciphertext, RoundKey[0]);
//        //轮函数
//        for (int i = 1; i < Nr + 1; i++) {
//            //S盒变换
//            ciphertext = ByteSub(ciphertext);
//            //行移位
//            ciphertext = ShiftRow(ciphertext);
//            //列混合
//            if (i != Nr) ciphertext = MixColumn(ciphertext);
//            //轮密钥加
//            ciphertext = AddRoundKey(ciphertext, RoundKey[i]);
//        }
//        return ciphertext;
//    }
//
//    /**
//     * 解密
//     * @param ciphertext  4个字长度的密文
//     * @param CipherKey   4、6或8个字长度的密钥
//     * @return
//     */
//    public static Word[] decrypt(Word[] ciphertext, Word[] CipherKey) {
////        Nb = 4;
//        Nk = CipherKey.length;
//        Nr = Nk + 6;
//        //解密密钥扩展
//        InvRoundKey = InvKeyExpansion(CipherKey);
//        Word[] plaintext = new Word[ciphertext.length];
//        for (int i = 0; i < ciphertext.length; i++)
//            plaintext[i] = new Word(ciphertext[i]);
//        //初始轮密钥加
//        plaintext = AddRoundKey(plaintext, InvRoundKey[Nr]);
//        //轮函数
//        for (int i = Nr - 1; i >= 0; i--) {
//            //S盒变换
//            plaintext = InvByteSub(plaintext);
//            //行移位
//            plaintext = InvShiftRow(plaintext);
//            //列混合
//            if (i != 0) plaintext = InvMixColumn(plaintext);
//            //轮密钥加
//            plaintext = AddRoundKey(plaintext, InvRoundKey[i]);
//        }
//        return plaintext;
//    }
//
//
//
//
//
//}
