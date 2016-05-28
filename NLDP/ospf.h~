#ifndef OSPF_H
#define OSPF_H

#include "ns3/object.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
namespace ns3{
namespace nldp{
//拓扑最大的节点数设为100
//生成之后，需要生成接口和Mac地址的映射信息表，包括RoutId,和请求的内容名字，意义对用的信息，用Vector容器保存;
const int maxnum = 100;
const int maxint = 999999;

//因为在ndnSIM中不存在ospf协议，为了实现ospf路由的功能写了一个Dijkstra;
class Dijkstra : public Object
{
 public:
  TypeId GetTypeId (void)
	{
  	static TypeId tid = TypeId ("ns3::Dijkstra")
     	.SetParent<Object> ()
     	.SetGroupName ("Dijkstra")
    	;
  	return tid;
	} 
     Dijkstra()
	{
           
           que = new int[maxnum];
	}
  virtual ~Dijkstra()
        {
            delete[] que;
 	    //  delete[] prev;
        }
//file:需要打开的文件路径名；
//number:目的节点；
void setFilename(string& filename)
{
   m_file = filename;
}
void setEndNumber(int endnum)
{
   m_endnum = endnum;
}
void setBeginNumber(int beginnum)
{
   m_beginnum = beginnum;
}
stack<int> Init()
    {
     //const string inputfile("/home/tjw/ndnSIM/ns-3/scratch/test.txt");
    ifstream file;
    file.open(static_cast<const char*>(m_file.c_str()));
    // 各数组都从下标1开始
  //   int* que = new int[maxnum];
   //  int*     dist = new int[maxnum];
   //  int*  prev = new int[maxnum];
   
    int dist[maxnum];
    int prev[maxnum];
    int c[maxnum][maxnum]; 

    string edgeId;
    int length;
    int delay;
    int bandwidth;
    int from;
    int to;
       
    int n = 0;
    int link = 0;
    
    istringstream lineBuffer;
    string line;
  
    getline (file,line);
    lineBuffer.str (line);
    
    lineBuffer >> n;
    lineBuffer >> link;

    for (int i = 0; i < n + 4 && !file.eof (); i++)
      {
        getline (file,line);
      }    // 输入结点数
    
    // 初始化c[][]为maxint
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            c[i][j] = maxint;
 
    for(int i=1; i<=link; ++i)  
    {
            getline (file,line);
       	    lineBuffer.clear ();
            lineBuffer.str (line);

            lineBuffer >> edgeId;
            lineBuffer >> from;
            lineBuffer >> to;
            lineBuffer >> length;
            lineBuffer >> delay;
            lineBuffer >> bandwidth;
           
            c[from+1][to+1] = delay;      
            c[to+1][from+1] = delay;     
    }
 
    for(int i=1; i<=n; ++i)
        dist[i] = maxint;
//输出数组中的元素值
/*
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j)
            cout<< c[i][j]<<"     ";
        cout<<" "<<endl;
    }
*/
    CreateGrap(n, m_beginnum, dist, prev, c);
    //int number = 4;
    // 最短路径长度,用来作为调试使用
    cout << "源点到第"<<m_endnum<<"个顶点的最短路径长度: " << dist[m_endnum] << endl;
 
    // 路径
    cout << "源点到第"<<m_endnum<<"个顶点的路径为: ";
    return searchPath(prev, m_beginnum, m_endnum);
    }


void CreateGrap(int n, int v, int *dist, int *prev, int c[maxnum][maxnum])
	{
		bool s[maxnum];    // 判断是否已存入该点到S集合中
    		for(int i=1; i<=n; ++i)
   		{
       		 dist[i] = c[v][i];
       		 s[i] = 0;     // 初始都未用过该点
       		 if(dist[i] == maxint)
            		prev[i] = 0;
       		 else
           		 prev[i] = v;
    	        }
    		dist[v] = 0;
    		s[v] = 1;
 
    	// 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
    	// 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
    	for(int i=2; i<=n; ++i)
    	{
       		 int tmp = maxint;
       		 int u = v;
        	// 找出当前未使用的点j的dist[j]最小值
        	for(int j=1; j<=n; ++j)
           	 if((!s[j]) && dist[j]<tmp)
            	{
               		 u = j;              // u保存当前邻接点中距离最小的点的号码
               		 tmp = dist[j];
           	}
        	s[u] = 1;    // 表示u点已存入S集合中
 
        	// 更新dist
        for(int j=1; j<=n; ++j)
            if((!s[j]) && c[u][j]<maxint)
            {
                int newdist = dist[u] + c[u][j];
                if(newdist < dist[j])
                {
                    dist[j] = newdist;
                    prev[j] = u;
                }
            }
    }
  }

stack<int> searchPath(int *prev,int v, int u)
{
    
    int tot = 1;
    que[tot] = u;
    tot++;
    int tmp = prev[u];
    while(tmp != v)
    {
        que[tot] = tmp;
        tot++;
        tmp = prev[tmp];
    }
    que[tot] = v;
    stack<int> s;
    for(int i=tot; i>=1; --i)
        if(i != 1)
          {
            s.push(que[i]);
            cout << que[i] << " -> ";
          }
        else
           {
            s.push(que[i]);
            cout << que[i] << endl;
           }
   return s;
}

private:
    int *que;
    string m_file;
    int m_beginnum;
    int m_endnum;
};
}//
}//namespace ns3
#endif

