//package com.xiets.aes;

import java.io.File;

/**
 * @author xietansheng
 */
public class Main {

    static private String DIRECTORY =  System.getProperty("user.dir");


    public static void main(String[] args) throws Exception {
//        String content = "Hello world!";        // 原文内容
        String key = "123456";                  // AES加密/解密用的原始密码
//
//        // 加密数据, 返回密文
//        byte[] cipherBytes = AESUtils.encrypt(content.getBytes(), key.getBytes());
//        // 解密数据, 返回明文
//        byte[] plainBytes = AESUtils.decrypt(cipherBytes, key.getBytes());
//        // 输出解密后的明文: "Hello world!"
//        System.out.println(new String(plainBytes));


        /*
         * AES 对文件的加密/解密
         */
        // 将 文件demo.jpg 加密后输出到 文件demo.jpg_cipher
        AESUtils.encryptFile(new File(DIRECTORY+"\\res\\cat.png"),
                new File(DIRECTORY+"\\res\\encrypt_file\\demo.jpg_cipher"), key.getBytes());

        // 将 文件demo.jpg_cipher 解密后输出到 文件demo.jpg_plain
        AESUtils.decryptFile(new File(DIRECTORY + "\\res\\encrypt_file\\demo.jpg_cipher"),
                new File(DIRECTORY+"\\res\\discrypt_file\\demo_plain.png"), key.getBytes());

        // 对比 原文件demo.jpg 和 解密得到的文件demo.jpg_plain 两者的 MD5 将会完全相同
    }

}
