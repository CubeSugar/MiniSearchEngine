MiniSearchEngine
================

---

##Project Time Schedule

LUD = last updata date

  N   |    LUD   |   Project Phase     |              Description
:-----|:---------|:--------------------|:-------------------------------------------
 01   | 20130730 | PreProcess          |
 02   | 20130809 | DelDuplicate        |
 03   | -        | CalcSimilarity      |
 04   | -        | QueryFrontEnd       |
 05   | -        | WebPage             |
  

### 1. PreProcess / Build Data Library File & Index ###



  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|: -------------------------------|:-----------------------------
 001  | 20130722 | 0.1    | generate_getfileinfo.py         | add:读取文件、解析内容方法
 002  | 20130722 | 0.1    | generate_ripepage.py            | add:生成抓取结果库文件
 003  | 20130730 | 0.1    | generate_queryindex.py          | add:生成关键词索引文件
 004  | 20130809 | 0.2    | generate_getfileinfo.py         | fix:解析方式，以空格替换任意空白符
 005  | 20130809 | 0.2    | generate_ripepage.py            | fix:不输出读取失败的文件、模拟重复


        

### 2. DelDuplicate & Build Query Keywords File ###


  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|: -------------------------------|:-----------------------------
 001  | 20130805 | 0.1    | Document.h                      | add:定义Document类
 002  | 20130805 | 0.1    | Document.cpp                    |
 003  | 20130805 | 0.1    | DocumentKits.h                  | add:读取正文、载入文件、转换编码函数
 004  | 20130805 | 0.1    | DocumentKits.cpp                |
 005  | 20130805 | 0.1    | QueryDemo.cpp                   | add:查询测试模块
 005  | 20130806 | 0.2    | Document.h                      | fix:以重载关系操作符代替比较函数
 006  | 20130806 | 0.2    | Document.cpp                    |
 007  | 20130806 | 0.2    | DocumentKits.h                  | add:分词、去重函数
 008  | 20130806 | 0.2    | DocumentKits.cpp                |
 009  | 20130808 | 0.3    | DocumentKits.h                  | update:封装为类
 010  | 20130808 | 0.3    | DocumentKits.cpp                |
 001  | 20130808 | 0.2    | QueryDemo.cpp                   | update:
 011  | 20130809 | 0.4    | DocumentKits.h                  | add:生成查询词库方法
 012  | 20130809 | 0.4    | DocumentKits.cpp                |
 000  | 20130809 | 0.3    | QueryDemo.cpp                   |

### 3. CalcSimilarity ###


  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|: -------------------------------|:-----------------------------
x |




### 4. QueryFrontEnd ###

  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|: -------------------------------|:-----------------------------
x |


---
## Issue ##

1. 读取数据文件编码问题


2. 读取文件标签匹配问题


3. 标题多于一行


4. 文章空白符、换行符处理方式


5. 生成文件索引的字节位置在query标签前


6. 取top10 受排序影响，同词频的词导致不同的top10，并影响结果


7. c++容器变量空间，堆／栈


8. c++ STL map<key, value>按value排序


9. 内存优化


10. CPU核心优化

---
## Q&A ##

1. 设计模式 单例模式etc

2. rebuild 重构概念



---
##Some Comment ##






