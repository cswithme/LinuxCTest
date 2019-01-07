/*
 * main.cpp
 *
 *  Created on: 2018-12-29
 *      Author: root
 */

#include "pugixml.hpp"

#include <stdio.h>
#include <string.h>
#include <iostream>

#define SLE_COM "/Afc/Config/ComXml.xml"

typedef struct _ST_XML_COM_INFO_
{
	char cComPath[128];//串口号
	bool bAdditionInfo; //是否指定 波特率等信息
	int iBaud;         //波特率
	char cParity;	   //校验位
	int iStopBit;      //停止位
	int iDataBit;      //数据位
}ST_XML_COM_INFO;

int main()
{

	using namespace pugi;

	bool bOk = true;
	ST_XML_COM_INFO stComInfo;

	xml_document doc;
	xml_parse_result rus = doc.load_file(SLE_COM);
	if (!rus) {
		printf("load_file  fail: %s\n", rus.description());
		bOk = false;
	}

	//	xpath_node nodeEntry = doc.select_nodes("/ComEnv/ComConfig/AgEntryQRCodeUnit");
	xml_node QREntryCfg;
	if(bOk){
		QREntryCfg = doc.child("ComEnv").child("ComConfig").child("AgEntryQRCodeUnit");
//		QREntryCfg = doc.select_node("/ComEnv/ComConfig/AgEntryQRCodeUnit").node(); //xpath
		if(QREntryCfg.empty()){
			printf("QREntryCfg is empty\n");
			bOk = false;
		}
	}

	xml_attribute attr;
	if(bOk){
		attr = QREntryCfg.attribute("compath");
		if(attr.empty()){
			printf("load compath is empty\n");
			bOk = false;
		}
		else{
			strncpy(stComInfo.cComPath, attr.value(), sizeof(stComInfo.cComPath));
		}
	}

	if(bOk){
		attr = QREntryCfg.attribute("otherinfo");
		if(attr.empty()){
			printf("load otherinfo is empty\n");
			bOk = false;
		}
		else{
			stComInfo.bAdditionInfo = attr.as_bool();
		}
	}

	xml_node QREntryDdditionalCfg;
	if(bOk && stComInfo.bAdditionInfo){
		QREntryDdditionalCfg = QREntryCfg.next_sibling();
		if(QREntryDdditionalCfg.empty()){
			printf("QREntryDdditionalCfg is empty\n");
			bOk = false;
		}
	}

	if(bOk && stComInfo.bAdditionInfo){
		attr = QREntryDdditionalCfg.attribute("baud");
		if(attr.empty()){
			printf("load baud is empty\n");
			bOk = false;
		}
		else{
			stComInfo.iBaud = attr.as_int(9600);
		}
	}

	if(bOk && stComInfo.bAdditionInfo){
		attr = QREntryDdditionalCfg.attribute("databit");
		if(attr.empty()){
			printf("load databit is empty\n");
			bOk = false;
		}
		else{
			stComInfo.iDataBit = attr.as_int(8);
		}
	}

	if(bOk && stComInfo.bAdditionInfo){
		attr = QREntryDdditionalCfg.attribute("parity");
		if(attr.empty()){
			printf("load parity is empty\n");
			bOk = false;
		}
		else{
			stComInfo.cParity = attr.value()[0];
		}
	}

	if(bOk && stComInfo.bAdditionInfo){
		attr = QREntryDdditionalCfg.attribute("stopbit");
		if(attr.empty()){
			printf("load stopbit is empty\n");
			bOk = false;
		}
		else{
			stComInfo.iStopBit = attr.as_int(1);
		}
	}

	if(bOk){
		printf("ComPath[%s]\n", stComInfo.cComPath);
		if(stComInfo.bAdditionInfo){
			printf("iBaud[%d], cParity[%c], iDataBit[%d], iStopBit[%d], \n", stComInfo.iBaud, stComInfo.cParity, stComInfo.iDataBit, stComInfo.iStopBit);
		}
	}



//    pugi::xml_document doc;
//
//    pugi::xml_parse_result rus = doc.load_file("./Debug/xgconsole.xml");
//    if (!rus) {
//    	printf("load_file xgconsole.xml fail: %s\n", rus.description());
//    	return -1;
//    }
//
//// tag::code[]
//    pugi::xpath_node_set tools = doc.select_nodes("/Profile/Tools/Tool[@AllowRemote='true' and @DeriveCaptionFrom='lastparam']");
//
//    std::cout << "Tools:\n";
//
//    for (pugi::xpath_node_set::const_iterator it = tools.begin(); it != tools.end(); ++it)
//    {
//        pugi::xpath_node node = *it;
//        std::cout << node.node().attribute("Filename").value() << "\n";
//    }
//
//    pugi::xpath_node build_tool = doc.select_node("//Tool[contains(Description, 'build system')]");
//
//    if (build_tool)
//        std::cout << "Build tool: " << build_tool.node().attribute("Filename").value() << "\n";
//// end::code[]


	return 0;
}
