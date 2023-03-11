import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;

// OK
// 生成文件 & 解密文件目录：D:\testFile
// 要加密的文件放在 D:\testFile\test.txt
// 加密：在D:\testFile\下生成encrypt_file.txt
// 解密：在D:\testFile\下生成output.txt
public class Test {
    private static final int ZERO = 0;
    private static final int ONE = 1;
    //实验操作路径
    private static String DIRECTORY = "D:\\testFiles\\";
    private static String PLAIN_TEXT_FILENAME = "test.txt"; // 测试的明文文件名
    private static String ENCRYOT_FILENAME = "encrypt_file.txt"; // 测试的明文文件名
    private static String OUTPUT_FILENAME = "output.txt"; // 测试的明文文件名

    public static void main(String[] args) {
        //key： 加密密钥
        String key = "aaaabbbbccccdddd";
        //ivParameter：AES cbc加密模式的iv向量
        String ivParameter = "AAAABBBBCCCCDDDD";
        try {
            //加密：
            encrypt(key, ivParameter);

            // 解密
            discrypt(key, ivParameter);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void encrypt(String key, String ivParameter) throws Exception {

        //将加密结果保存在 ENCRYOT_FILENAME 中
        String fileName1 = ENCRYOT_FILENAME;
        File file2 = new File(DIRECTORY + "/" + PLAIN_TEXT_FILENAME);
        encryptfile(file2, key, ivParameter, fileName1);
    }

    private static void discrypt(String key, String ivParameter) throws Exception {
        //对给出的密文的解密过程。
        //密文保存在“密文.txt”中
        //将解密结果保存在“明文.txt”中

        File file = new File(DIRECTORY + "/" + ENCRYOT_FILENAME);
        String fileName = OUTPUT_FILENAME;
        decriptfile(file, key, ivParameter, fileName); // #BUG
    }

    /**
     * 文件处理方法
     * code为加密或者解密的判断条件
     * file 密文文件
     * key 加密密钥
     * ivParameterm iv向量
     * filename 加解密结果存入的文件名
     */
    public static void doFile(int code, File file, String key, String ivParameterm, String filename) throws Exception {
        BufferedInputStream bis = new BufferedInputStream(new FileInputStream(
                file));
        byte[] bytIn = new byte[(int) file.length()];
        bis.read(bytIn);
        bis.close();

        // AES加密
        byte[] raw = key.getBytes("ASCII");
        SecretKeySpec skeySpec = new SecretKeySpec(raw, "AES");
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        //Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        IvParameterSpec iv = new IvParameterSpec(ivParameterm.getBytes());

        if (0 == code) {
            cipher.init(Cipher.ENCRYPT_MODE, skeySpec, iv); //加密
        } else if (1 == code) {
            cipher.init(Cipher.DECRYPT_MODE, skeySpec, iv); //解密
        }

        // 写文件
        byte[] bytOut = cipher.doFinal(bytIn);
        File outfile = new File(DIRECTORY + "/" + filename);
        BufferedOutputStream bos = new BufferedOutputStream(
                new FileOutputStream(outfile));
        bos.write(bytOut);
        bos.close();
    }

    //文件加密
    public static void encryptfile(File file, String key, String ivParameter, String filename) throws Exception {
        doFile(ZERO, file, key, ivParameter, filename);
    }

    //文件解密
    public static void decriptfile(File file, String key, String ivParameter, String filename) throws Exception {
        doFile(ONE, file, key, ivParameter, filename);
    }
}
