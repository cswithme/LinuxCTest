/*! \file 	PubXml.h	
* \version  	1.0		
* \brief  	xml解析		
* \author	liuyp						
* \date		2009-06-15		
* \par		修改记录			
*  
* \par
			
* \par:	
*/


#ifndef PUBXML_H_
#define PUBXML_H_

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <cassert>
#include <string>
#include <vector>
using namespace std;


#ifdef __cplusplus                    
extern "C"                             
{
#endif


#ifndef ARR_CHAR_LENGTH
#define ARR_CHAR_LENGTH	256
#endif 

#define XML_CODE_FORMAT  "UTF-8"

//class CParamVersion;


/*! \class		CPubXml
* \version		1.0			
* \brief  	    基于libxml2库的封装类
* \author		liuyp
* \date			2009-06-15
* \par			修改记录
*  
* \par
				
* \par:	
*/

class CPubXml
{
public:
	/*! \fn CPubXml::CPubXml()
	 * \brief  构造函数
	 * \author liuyp
	 * \date   2011-01-15
	*/	
	CPubXml();
	/*! \fn CPubXml::~CPubXml()
	 * \brief  析构函数
	 * \author liuyp
	 * \date   2011-01-15
	*/	
	virtual ~CPubXml();
	
	//friend class CParamVersion;
	
public:

	/*! \fn CPubXml::LoadXmlFile(const char *pszXmlFileName, const char *pszXmlFileEnCoding)
	 * \brief 加载XML文件
	
	 * \param[in] 	pszXMLFileName		XML文件名
	 * \param[in] 	pszXmlFileEnCoding	XML文件编码
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool LoadXmlFile(const char *pszXmlFileName, const char *pszXmlFileEnCoding ="utf8");	//加载xml文件
	/*! \fn CPubXml::GetNodeSetByPath(const char *pszKeyPath)
	 * \brief 通过指定的节点路径，获取节点集
	
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetNodeSetByPath(const char *pszKeyPath);	//通过路径获取节点集
	/*! \fn CPubXml::GetNodeSetByPath(const char *pszKeyPath, xmlXPathObjectPtr *pxXmlXPathPtr)
	 * \brief 通过指定的节点路径，获取节点集
	
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[out] 	pxXmlXPathPtr 节点路径指向的上下文节点
	 * \return 		bool 返回类型
	 * \author 		miqiang
	 * \date 		2011-05-06
	*/
	bool GetNodeSetByPath(const char *pszKeyPath, xmlXPathObjectPtr *pxXmlXPathPtr);	//通过路径获取节点集
	
	//获取节点内容
	/*! \fn CPubXml::GetValue(char *pszValue) const
	 * \brief 获取节点内容或节点内容列表
	
	 * \param[in] 	
	 * \param[out] 	pszValue	节点内容
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetValue(char *pszValue) const;
	
	/*! \fn CPubXml::GetValue(int *piValue) const
	 * \brief 获取节点内容或节点内容列表
	 * \param[in] 	
	 * \param[out] 	piValue	节点内容
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetValue(int *piValue) const;
	
	/*! \fn CPubXml::GetValue(bool *pbValue) const
	 * \brief 获取节点内容或节点内容列表
	 * \param[in] 	
	 * \param[out] 	pbValue	节点内容
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetValue(bool *pbValue) const;
	
	/*! \fn CPubXml::GetValue(vector<string> &vecValue) const
	 * \brief 获取节点内容或节点内容列表
	
	 * \param[in] 	
	 * \param[out] 	vecValue 节点内容列表
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetValue(vector<string> &vecValue) const;
	
	/*! \fn CPubXml::GetAttrbute(const int iNum, const char *pszAttrName, char* pszAttrbute) const
	 * \brief 		获取并列节点中第Num个节点的属性
	 * \param[in] 	pszAttrName 属性名称	iNum :节点序号，从0开始
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 			2011-09-01
	*/
	bool GetAttrbute(const int iNum, const char *pszAttrName, char* pszAttrbute) const;


	/*! \fn CPubXml::GetAttrbute(const int iNum, const char *pszAttrName, char* pszAttrbute) const
	 * \brief 		获取并列节点中第Num个节点的属性
	 * \param[in] 	pszAttrName 属性名称	iNum :节点序号，从0开始
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 			2011-09-01
	*/
	bool GetAttrbute(const int iNum, const char *pszAttrName, string &strAttrbute) const;

	/*! \fn CPubXml::GetAttrbute(const char *pszAttrName, char* pszAttrbute) const
	 * \brief 通过属性名，获取属性值或属性值列表
	
	 * \param[in] 	pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszAttrName, char *pszAttrbute) const;
	
	/*! \fn CPubXml::GetAttrbute(const char *pszAttrName, int *piAttrbute) const
	 * \brief 通过属性名，获取属性值或属性值列表
	
	 * \param[in] 	pszAttrName 属性名称
	 * \param[out] 	piAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszAttrName, int  *piAttrbute) const;
	
	/*! \fn CPubXml::GetAttrbute(const char *pszAttrName, int *piAttrbute) const
	 * \brief 通过属性名，获取属性值或属性值列表

	 * \param[in] 	pszAttrName 属性名称
	 * \param[out] 	piAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-09-02
	*/
	bool GetAttrbute(const int iNum, const char *pszAttrName, int *piAttrbute) const;




	/*! \fn CPubXml::GetAttrbute(const char *pszAttrName, bool* pbAttrbute) const
	 * \brief 通过属性名，获取属性值或属性值列表
	
	 * \param[in] 	pszAttrName 属性名称
	 * \param[out] 	pbAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszAttrName, bool *pbAttrbute) const;
	
	/*! \fn CPubXml::GetAttrbute(const char *pszAttrName, vector<string> &vecAttrbute) const
	 * \brief 通过属性名，获取属性值或属性值列表
	
	 * \param[in] 	pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值列表
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszKey, vector<string> &vecAttrbute) const;
	

	/*! \fn CPubXml::GetAttrbute(const char *pszAttrName, bool* pbAttrbute) const
	 * \brief 		通过属性名，获取属性值或属性值列表
	 * \param[in] 	pszAttrName 属性名称
	 * \param[out] 	pbAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 			2011-09-02
	*/
	bool GetAttrbute(const char *pszAttrName, string &strAttrbute) const;

	/*! \fn CPubXml::GetAttrbute(const char *pszAttrName, vector<string> &vecAttrbute) const
	 * \brief 通过属性名，获取属性值或属性值列表
	 * \param[in] 	pszConditionAttrName条件属性名，pszConditionAttrbute条件属性值
	 * 				pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-08-31
	*/
	bool GetAttrbute(const char* pszConditionAttrName, const char*pszConditionAttrbute, const char *pszAttrName, char *pszAttrbute) const;

	/*! \fn CPubXml::GetAttrbute(const char* pszConditionAttrName1, const char*pszConditionAttrbute1,
									const char* pszConditionAttrName2, const char*pszConditionAttrbute2,
									const char *pszAttrName, char *pszAttrbute) const
	 * \brief			有条件的获取属性值
	 * \param[in] 	pszConditionAttrName1条件1属性名，pszConditionAttrbute1条件1属性值
	 * 				pszConditionAttrName1条件2属性名，pszConditionAttrbute2条件1属性值
	 * 				pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-08-31
	*/
	bool GetAttrbute(const char* pszConditionAttrName1, const char*pszConditionAttrbute1,
									const char* pszConditionAttrName2, const char*pszConditionAttrbute2,
									const char *pszAttrName, char *pszAttrbute) const;

	/*! \fn CPubXml::etChildAttrbute(const char* pszParentAttrName, const char*pszParentAttrbute,
									const char *pszAttrName, char *pszAttrbute) const
	 * \brief			通过父节点的条件获取子节点属性值
	 * \param[in] 	pszParentAttrName条件1属性名，pszParentAttrbute条件1属性值
	 * 				pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-08-31
	*/
	bool GetChildAttrbute(const char* pszParentAttrName1, const char*pszParentAttrbute1,
									const char *pszAttrName, char *pszAttrbute) const;

	/*! \fn CPubXml::etChildAttrbute(const char* pszParentAttrName, const char*pszParentAttrbute,
									const char *pszAttrName, char *pszAttrbute) const
	 * \brief			获取同一父节点的第Num个子节点的属性值
	 * \param[in] 	pszParentAttrName条件1属性名，pszParentAttrbute条件1属性值, Num:子节点的序号,从0开始
	 * 				pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-08-31
	*/
	bool GetChildAttrbute(const int iNum, const char* pszParentAttrName, const char*pszParentAttrbute,
									const char *pszAttrName, char *pszAttrbute) const;


	/*! \fn CPubXml::etChildAttrbute(const char* pszParentAttrName, const char*pszParentAttrbute,
									const char *pszAttrName, char *pszAttrbute) const
	 * \brief			获取同一父节点的第Num个子节点的属性值
	 * \param[in] 	pszParentAttrName条件1属性名，pszParentAttrbute条件1属性值, Num:子节点的序号,从0开始
	 * 				pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-08-31
	*/
	bool GetChildAttrbute(const int iNum, const char* pszParentAttrName, const char*pszParentAttrbute,
									const char *pszAttrName, int *piAttrbute) const;


	/*! \fn CPubXml::GetBrotherNoteNum() const
	 * \brief			获取当前路径下兄弟节点的个数
	 * \param[in] 	pszParentAttrName条件1属性名，pszParentAttrbute条件1属性值
	 * 				pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-08-31
	*/
	int GetBrotherNoteNum();

	/*! \fn CPubXml::GetBrotherNoteNum() const
	 * \brief			获取当前路径下符合某属性的兄弟节点的个数
	 * \param[in] 	pszParentAttrName条件1属性名，pszParentAttrbute条件1属性值
	 * 				pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		jiangzj
	 * \date 		2011-08-31
	*/
	int GetBrotherNoteNum(const char* pszConditionAttrName, const char*pszConditionAttrbute);

	/*! \fn CPubXml::SetValue(const char *pszValue) const
	 *  \brief 设置节点内容
	 * \param[in] 	pszValue 节点内容
	 * \param[out] 	
	 * \return 		void 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	void SetValue(const char *pszValue) const;	
	
	/*! \fn CPubXml::SetValue(const int iValue) const
	 * \brief 设置节点内容
	
	 * \param[in] 	pszValue 节点内容
	 * \param[out] 	
	 * \return 		void 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	void SetValue(const int  iValue) const;
	
	/*! \fn CPubXml::SetValue(const bool bValue) const
	 * \brief 设置节点内容
	
	 * \param[in] 	bValue 节点内容
	 * \param[out] 	
	 * \return 		void 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	void SetValue(const bool bValue) const;
	
	/*! \fn CPubXml::SetAttrbute(const char *pszAttrName, const char *pszAttrBute) const
	 * \brief 设置属性值
	
	 * \param[in] 	pszAttrName 属性名
	 * \param[in] 	pszAttrBute 属性值
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetAttrbute(const char *pszAttrName, const char *pszAttrBute) const;
	
	/*! \fn CPubXml::SetAttrbute(const char *pszAttrName, const int iAttrBute) const
	 * \brief 设置属性值
	 * \param[in] 	pszAttrName 属性名
	 * \param[in] 	iAttrBute 属性值
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetAttrbute(const char *pszAttrName, const int iAttrBute) const;
	
	/*! \fn CPubXml::SetAttrbute(const char *pszAttrName, const bool bAttrBute) const
	 * \brief 设置属性值
	 * \param[in] 	pszAttrName 属性名
	 * \param[in] 	bAttrBute 属性值
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetAttrbute(const char *pszAttrName, const bool bAttrBute) const;	
	
	/*! \fn CPubXml::SaveXmlFile() const
	 * \brief 	保存xml文件
	 * \param[in] 	
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SaveXmlFile() const;
	
	/*! \fn CPubXml::FreeXmlPathContext()
	 * \brief 清理XPath查询环境
	 * \param[in] 	
	 * \param[out] 	
	 * \return 		void 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	void FreeXmlPathContext();	
	
public:
	
	/*! \fn CPubXml::GetValue(const char *pszKeyPath, char *pszValue) 
	 * \brief 获取节点内容或节点内容列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[out] 	pszValue	节点内容
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetValue(const char *pszKeyPath, char *pszValue);
	
	/*! \fn CPubXml::GetValue(const char *pszKeyPath, int *piValue) 
	 * \brief 获取节点内容或节点内容列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[out] 	piValue	节点内容
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/		
	bool GetValue(const char *pszKeyPath, int *piValue);
	
	/*! \fn CPubXml::GetValue(const char *pszKeyPath, bool *pbValue) 
	 * \brief 获取节点内容或节点内容列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[out] 	pbValue	节点内容
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetValue(const char *pszKeyPath, bool *pbValue);
	
	/*! \fn CPubXml::GetValue(const char *pszKeyPath, vector<string> &vecValue)
	 * \brief 获取节点内容或节点内容列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[out] 	vecValue 节点内容列表
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetValue(const char *pszKeyPath, vector<string> &vecValue);
	
	/*! \fn CPubXml::GetAttrbute(const char *pszKeyPath, const char *pszAttrName, char* pszAttrbute)
	 * \brief 通过属性名，获取属性值或属性值列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[in]	pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszKeyPath, const char *pszAttrName, char *pszAttrbute) ;
	
	/*! \fn CPubXml::GetAttrbute(const char *pszKeyPath, const char *pszAttrName, int *piAttrbute)
	 * \brief 通过属性名，获取属性值或属性值列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[in]	pszAttrName 属性名称
	 * \param[out] 	piAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszKeyPath, const char *pszAttrName, int  *piAttrbute) ;
	
	/*! \fn CPubXml::GetAttrbute(const char *pszKeyPath, const char *pszAttrName, bool* pbAttrbute)
	 * \brief 通过属性名，获取属性值或属性值列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[in]	pszAttrName 属性名称
	 * \param[out] 	pbAttrbute属性值
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszKeyPath, const char *pszAttrName, bool *pbAttrbute) ;
	
	/*! \fn CPubXml::GetAttrbute(const char *pszKeyPath, const char *pszAttrName, vector<string> &vecAttrbute)
	 * \brief 通过属性名，获取属性值或属性值列表
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[in]	pszAttrName 属性名称
	 * \param[out] 	pszAttrbute属性值列表
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool GetAttrbute(const char *pszKeyPath, const char *pszKey, vector<string> &vecAttrbute) ;
	
	/*! \fn CPubXml::SetValue(const char *pszKeyPath, const char *pszValue)
	 * \brief 设置节点内容
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[in]	pszValue 节点内容
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetValue(const char *pszKeyPath, const char *pszValue) ;

	/*! \fn CPubXml::SetValue(const char *pszKeyPath, const int iValue)
	 * \brief 设置节点内容
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[in]	iValue 节点内容
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/		
	bool SetValue(const char *pszKeyPath, const int  iValue) ;
	
	/*! \fn CPubXml::SetValue(const char *pszKeyPath, const bool bValue)
	 * \brief 设置节点内容
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[in]	bValue 节点内容
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetValue(const char *pszKeyPath, const bool bValue) ;
	
	/*! \fn CPubXml::SetAttrbute(const char *pszKeyPath, const char *pszAttrName, const char *pszAttrBute)
	 * \brief 设置属性值
	 * \param[in]   pszKeyPath  节点路径
	 * \param[in] 	pszAttrName 属性名
	 * \param[in] 	pszAttrBute 属性值
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetAttrbute(const char *pszKeyPath, const char *pszAttrName, const char *pszAttrBute) ;
	
	/*! \fn CPubXml::SetAttrbute(const char *pszKeyPath, const char *pszAttrName, const int iAttrBute)
	 * \brief 设置属性值
	 * 
	 * \param[in]   pszKeyPath  节点路径
	 * \param[in] 	pszAttrName 属性名
	 * \param[in] 	iAttrBute 属性值
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetAttrbute(const char *pszKeyPath, const char *pszAttrName, const int iAttrBute) ;
	
	/*! \fn CPubXml::SetAttrbute(const char *pszKeyPath, const char *pszAttrName, const bool bAttrBute)
	 * \brief 设置属性值
	 * 
	 * \param[in]   pszKeyPath  节点路径
	 * \param[in] 	pszAttrName 属性名
	 * \param[in] 	bAttrBute 属性值
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		liuyp
	 * \date 		2011-01-15
	*/	
	bool SetAttrbute(const char *pszKeyPath, const char *pszAttrName, const bool bAttrBute) ;	

	/*! \fn CPubXml::CreateXmlFile(const char *pszXmlFileName, const char *pszXmlFileEnCoding ="utf8")
	 * \brief 创建xml文件
	
	 * \param[in] 	pszXMLFileName		XML文件名
	 * \param[in] 	pszXmlFileEnCoding	XML文件编码
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	bool CreateXmlFile(const char *pszXmlFileName, const char *pszXmlFileEnCoding ="utf8");	//创建xml文件

	/*! \fn CPubXml::CreateRootNode(const char *pszRootName)
	 * \brief 创建根节点
	 * 
	 * \param[in] 	pszRootName		根节点名
	 * \param[out] 	
	 * \return 		xmlNodePtr 		返回指向根节点的指针
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	xmlNodePtr CreateRootNode(const char *pszRootName);

	/*! \fn CPubXml::CreateNodeAppend(const char *pszNodeName, xmlNodePtr ptrParentNode)
	 * \brief 创建节点并添加至父节点
	 * 
	 * \param[in] 	pszNodeName		节点名
	 * \param[in] 	ptrParentNode		父节点
	 * \param[out] 	
	 * \return 		xmlNodePtr 		返回指向拟添加节点的指针
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	xmlNodePtr CreateNodeAppend(const char *pszNodeName, xmlNodePtr ptrParentNode);	//创建节点并添加至父节点

	/*! \fn CPubXml::RemoveNode(xmlNodePtr ptrNode)
	 * \brief 删除节点
	 * 
	 * \param[in] 	ptrNode		节点名
	 * \param[out] 	
	 * \return 		bool 		返回bool类型
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	bool RemoveNode(xmlNodePtr ptrNode);	//删除节点
	
	/*! \fn CPubXml::RemoveAllChildren(xmlNodePtr ptrParentNode)
	 * \brief 删除节点的所有直接点
	 * 
	 * \param[in] 	ptrParentNode		父节点
	 * \param[out] 	
	 * \return 		int 		返回删除的子节点个数
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	int RemoveAllChildren(xmlNodePtr ptrParentNode);	//删除节点的所有直接点
	
	/*! \fn CPubXml::GetNodeSet(const char *pszKeyPath)
	 * \brief 通过指定的节点路径，获取节点集
	
	 * \param[in] 	pszKeyPath 节点路径
	 * \param[out] 	
	 * \return 		xmlXPathObjectPtr 返回节点路径指向的上下文节点的指针
	 * \author 		miqiang
	 * \date 		2011-05-06
	*/
	xmlXPathObjectPtr GetNodeSet(const char *pszKeyPath);	//通过路径获取节点集
	
	/*! \fn CPubXml::GetAttribute(const xmlNodePtr node, const char *pszAttrName, char *pszAttrValue)
	 * \brief 获取指定节点的某个属性节点的值
	 * 
	 * \param[in]   	node  节点对象指针
	 * \param[in]		pszAttrName 属性名称
	 * \param[out] 	pszAttrValue	属性值
	 * \return 		bool 返回类型
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	bool GetAttribute(const xmlNodePtr node, const char *pszAttrName, char *pszAttrValue) ;	

	/*! \fn CPubXml::GetValue(const xmlNodePtr node, char *pszAttrValue)
	 * \brief 获取指定节点的内容
	 *
	 * \param[in]   	node  节点对象指针
	 * \param[out] 	pszValue	节点内容
	 * \return 		bool 返回类型
	 * \author 		miqiang
	 * \date 			2014-04-18
	*/
	bool GetValue(const xmlNodePtr node, char *pszValue) ;
	
	/*! \fn CPubXml::SetValue(const char *pszKeyPath, const char *pszValue)
	 * \brief 设置指定节点内容，针对新创建的节点将添加文本节点
	 * 
	 * \param[in]   	node  节点对象指针
	 * \param[in]		pszValue 节点内容
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	bool SetValue(xmlNodePtr node, const char *pszValue) ;	
	
	/*! \fn CPubXml::SetAttrbute(xmlNodePtr node, const char *pszAttrName, const char *pszAttrValue)
	 * \brief 设置指定节点的属性值，针对新创建的节点将添加属性值
	 * 
	 * \param[in]   	node  节点对象指针
	 * \param[in] 	pszAttrName 属性名
	 * \param[in] 	pszAttrValue 属性值
	 * \param[out] 	
	 * \return 		bool 返回类型
	 * \author 		miqiang
	 * \date 			2012-01-05
	*/	
	bool SetAttrbute(xmlNodePtr node, const char *pszAttrName, const char *pszAttrValue) ;	
		
private:
	char m_szFileName[ARR_CHAR_LENGTH];    /*全路径*/
	xmlDocPtr  m_xmlDocPtr;               	/*xml文件句柄*/
	xmlXPathContextPtr m_xpathContextPtr;	/*XPATH上下文指针*/
	xmlXPathObjectPtr  m_xpathPtr ;         /*XPATH对象指针*/
	int m_BrotherNoteNum;					/*兄弟节点的个数*/
};

#ifdef __cplusplus 		 
}
#endif/*__cplusplus*/
#endif /*PUBXML_H_*/
