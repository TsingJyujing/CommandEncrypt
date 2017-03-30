# 指令加密系统
这套程序是为了对轻量的指令（不超过124字节）进行加密的系统，其中使用Java生成公钥和私钥对，而采用纯C编写了库函数，在自测和调试的时候使用了C++。
## 简介
## 密钥生成器
```java
RSAUtility ru = new RSAUtility();
ru.generateKey(1024);
```
以上代码用来生成一对密钥，密钥存储在对象中。
```java
PrintData.saveFlipByteArray(ru.publicKey.getPublicExponent().toByteArray(), "public_key.hex");
```
以上代码用来将公钥存到文件中，这个hex文件可以被C程序读取。
## 使用C/C++版本的程序对数据作加密解密和签名
参看cmd_encrypt.h文件，其中有详细的注释。
