# spellingAssociate项目文档 #
### 简介 ###
> spellingAssociate是在Linux系统下用C++基于对象的方法编写的一个单词输入联想纠错程序，项目实现的效果是：客户端输入一个单词，服务器收到客户端发送过来的单词后在本地词典中找到一个和它最相近的一个单词并返回给客户端。
> 
> 本地词典包括中文单词和英文单词，事先对原始语料进行预处理，分离单词并统计词频保存到文件。
> 
> 客户端请求的单词以及服务器返回的结果会保存在cache文件，加快下次查找速度



### 项目流程图 ###
![项目流程图](https://github.com/meihao1203/spellingAssociate/blob/master/spellingAssociate%E6%B5%81%E7%A8%8B%E5%9B%BE.png)



### 项目框架 ###
1. 线程池 
![Threadpool](https://github.com/meihao1203/spellingAssociate/blob/master/Threadpool.png)

----------

2. 服务器框架 
![TcpServer](https://github.com/meihao1203/spellingAssociate/blob/master/TcpServer.png)

----------

3. 定时器线程 

![TimerThread](https://github.com/meihao1203/spellingAssociate/blob/master/TimerThread.png)

----------

4. 任务类 
![MyTask](https://github.com/meihao1203/spellingAssociate/blob/master/MyTask.png)

----------

5. 项目总体框架 
![spellingAssociate](https://github.com/meihao1203/spellingAssociate/blob/master/spellingAssociate.png)

----------

6. 离线部分类 

![offline](https://github.com/meihao1203/spellingAssociate/blob/master/offline.png)



### 项目运行效果 ###
![run_result](https://github.com/meihao1203/spellingAssociate/blob/master/run_result.png)



### 其他技术细节 ###
1. cppjieba开源库对中文语料分词
2. log4cpp开源库记录项目运行日志
3. 最小编辑距离算法计算单词准换所需的最少编辑操作
4. utf-8编码解析
