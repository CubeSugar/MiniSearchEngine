MiniSearchEngine
================

__文档版权：__ 自由转载－非商用－非衍生－保持署名 / Creative Commons Attribution-NonCommercial-NoDerivs 3.0

__代码版权：__ GPLv3

## Brief Introduction ##
---
### 1. Description ###

搜索引擎迷你项目，将网页/文本数据建库，去重，计算相似度生成检索资源；编写Linux守护进程以支持前台页面的查询请求。

项目关键词：**分词**、**余弦相似度**、**VSM**、**倒排索引**、**守护进程**、**网络编程**等

### 2. Develop Environment ###

+ Ubuntu 12.04

+ g++ 4.6.3

+ python 3.3.2

### 3. Directory Arch ###

<p>
MiniSearchEngine<br>
┣ bin<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ Configuration.cpp<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ dem.cppo<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ Document.cpp<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ DocumentKits.cpp<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ SearchEngineServer.cpp<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ TcpSocket.cpp<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┗ QueryClientDemo<br>
┣ data<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ Raw_Data<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ ripepage.lib<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ query.lib<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┗ index.lib<br>
┣ include<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ Configuration.h<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ Document.h<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ DocumentKits.h<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ MiniSearchEngineStd.h<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┗ TcpSocket.h<br>
┣ lib<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┣ libcode.a<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┗ libelus.a<br>
┣ log<br>
┣ src<br>
┃&nbsp;&nbsp;&nbsp;&nbsp;┗ stopwordlist.txt<br>
┣ search_engine.conf<br>
┗ Makefile<br>
</p>


### 4. Module ###

#### index.lib ####
从ripepage.lib中读取query word的偏移位置，存储在index.lib文件中，格式如下：
	
	queryword1 \t offset1
	queryword2 \t offset2
	…
	

#### WordSegement ####

调用分词库libcode.a libelus.a进行分词。

分词原理的学习附在Reference部分。

#### Delete Duplicate ####

1. 指纹法去重

	特征码：该网页/文本中词频最高的10个词；
	判重算法：对于每两篇，比较topword10的交集，如果交集大于6个，则认为是互为重复的网页。

2. 特征码去重

	特征码：提取该网页/文本中每个逗号前后的5个字节，将这些字符串顺序连接成一个特征字符串S。
	判重算法：对于两篇网页/文本，计算S1和S2的LCS，如果len(LCS)/min(len(S1), len(S2)) > 0.6则判定为重复。

去重后生成一个全词集合文本，格式如下：

	word1 \t docid_i \t offset_i \t docid_k \t offset_k \t …
	word2 \t docid_j \t offset_j \t …
	…
	


#### Calculate Similarity ####

网页/文本相似度计算基于VSM与余弦相似度，本项目中采用简化模型“tf-idf”。

VSM、余弦相似度的相关资料附在Reference部分。

#### SearchEngineServer Daemon Process ####
Linux 守护进程，实现cache

#### Front End ####
使用PHP编写的前端网页


##Project Time Schedule ##
---
LUD = last update date

  N   |    LUD   |   Project Phase     |              Description
:-----|:---------|:--------------------|:-------------------------------------------
 01   | 20130809 | PreProcess          |
 02   | 20130809 | DelDuplicate        |
 03   | 20130812 | CalcSimilarity      |
 04   | 20130815 | SearchEngineServer  | DaemonProcess
 05   | -        | QueryFrontEnd       | PHP WebPage
  

### 1. PreProcess / Build Data Library File & Index ###


  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|:--------------------------------|:-----------------------------
 001  | 20130722 | 0.1    | getfileinfo.py                  | add:读取文件、解析内容方法
 002  | 20130722 | 0.1    | ripepage.py                     | add:生成抓取结果库文件
 003  | 20130730 | 0.1    | queryindex.py                   | add:生成关键词索引文件
 004  | 20130809 | 0.2    | getfileinfo.py                  | fix:解析方式，以空格替换任意空白符
 005  | 20130809 | 0.2    | ripepage.py                     | fix:不输出读取失败的文件、模拟重复



### 2. DelDuplicate & Build Query Keywords File ###


  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|:--------------------------------|:-----------------------------
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
 013  | 20130809 | 0.3    | QueryDemo.cpp                   |
 014  | 20130815 | 0.1    | Configuration.h                 | add:配置类
 015  | 20130815 | 0.1    | Configuration.cpp               |

### 3. CalcSimilarity ###


  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|:--------------------------------|:-----------------------------
 001  | 20130812 | 0.5    | DocumentKits.h                  | add:初始化文档向量、计算相似度方法
 002  | 20130812 | 0.5    | DocumentKits.cpp                |
 003  | 20130812 | 0.4    | QueryDemo.cpp                   | update:测试计算相似度


### 4. SearchEngineServer ###

  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|:--------------------------------|:-----------------------------
 001  | 20130815 | 0.1    | TcpSocket.h                     | add: 封装TCP 函数
 002  | 20130815 | 0.1    | TcpSocket.cpp                   |
 003  | 20130815 | 0.1    | SearchEngineServer.cpp          | add: 搜索引擎后台守护进程




### 5. QueryFrontEnd ###

  N   |    LUD   |    V   |             code file           |          Description       
:----:|:---------|:-------|:--------------------------------|:-----------------------------
- |



## Issue ##
---
1. 读取数据文件编码问题


2. 读取文件标签匹配问题


3. 标题多于一行


4. 文章空白符、换行符处理方式


5. 生成文件索引的字节位置在query标签前


6. 取top10 受排序影响，同词频的词导致不同的top10，并影响结果


7. c++容器变量空间，堆／栈


8. c++ STL map<key, value>按value排序


9. 内存优化


10. 多线程优化


## Q & A ##
---





## Some Comment ##
---
1. 设计模式 单例模式etc

2. rebuild 重构概念

3. 缓存cache

---
## Reference ##

1. 分词原理
2. VSM
3. 余弦相似度
4. 文本聚类





