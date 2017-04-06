# 指令加密系统
这套程序是为了对轻量的指令（不超过120字节）进行加密的系统。
如果
其中使用Java生成公钥和私钥对，而采用符合C89标准的C语言编写了库函数。
**这些程序经过了Win/Linux上的GCC（Win上位TDM-GCC或者MinGW）的编译和测试，以及ARM指令集编译器ARMCC的编译（尚未测试），任何修改至少请在ARMCC和GCC上通过编译。**

## 简介
这是一套
### 密钥生成器（Java）
```java
RSAUtility ru = new RSAUtility();
ru.generateKey(1024);
```
以上代码用来生成一对密钥，密钥存储在对象中。
```java
PrintData.saveFlipByteArray(ru.publicKey.getPublicExponent().toByteArray(), "public_key.hex");
```
以上代码用来将公钥存到文件中，这个hex文件可以被C程序读取。
直接运行Java程序就可以获得密钥了。
**请妥善保存生成的私钥文件，需要严格保密才能保证安全性。**

### 使用C版本的程序对数据作加密解密和签名
由于文件中的注释已经比较清晰了，所以不再写详细的文档，参看每个**头文件**中的注释。
**注意！加密的随机盐和种子有关系，如果需要更高的安全性请使用Unix时间初始化种子**
```C
srand(time);
```
### 配置文件的修改
主要修改`rsa_common.h`中的两处，注释代码可以改变代码行为。
```C
// 是否使用GMP库，目前只能使用GMP或者MINI-GMP
#define USE_GMP_LIBRARY

// 是否对数据进行自校验，如果协议有校验，就可以取消
// 注释掉下面这一句即可取消校验
#define USE_INNER_VALIDATION
```