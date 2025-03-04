# -*- coding: utf-8 -*-


import requests
import json
import threading
from threading import Thread
from dbconn2025 import DBConn
from datetime import datetime
import urllib.request
from urllib.parse import urlparse
import sys
import base64
import os
import time


#学校清单
# schoolListUrl="https://gaokao.baidu.com/gk/gkschool/list?province=&city=&batch=&character=&type=&education=&nature=&needFilter=0&rn=10&"
schoolListUrl="https://gaokao.baidu.com/gk/gkschool/list?rn=10&"
#分数线，针对浙江3+3
schoolScoreUrl="https://gaokao.baidu.com/gk/gkschool/schoolscore?curriculum=3%2B3综合&"
# 参数pn-页数，school-中文学校名，province-省，year-年份
schoolMajorScoreUrl="https://gaokao.baidu.com/gk/gkschool/majorscore?rn=10&curriculum=&subject=&sortType&version=2&needFilter=1&"
# 参数pn-第几条记录开始，query-中文学校名，province-省，year-年份,curriculum-课程类型,3+3综合,rn-每页记录数
schoolPlanUrl="https://gaokao.baidu.com/gk/gkschool/getrecruitingscheme?curriculum=3%2B3综合"

schoolFieldList=["\"college_name\"" ,"\"rankTypeShow\"" ,"rankType","rank",\
    "globalRank","\"uniqueRank\"","province","city","location",\
    "school_type","\"education\"","nature","batch","score_city",\
    "score_list","tag","logourl"]

schoolScoreFieldList=["\"legalName\"","province","year","curriculum",\
    "\"batchName\"","\"enrollType\"","\"minScore\"","\"minScoreOrder\"",\
    "\"minCha\"","\"enrollNum\""]

schoolMajorScoreFieldList=["\"legalName\"" ,"\"majorName\"","province","year",\
    "curriculum","\"batchName\"","tags","\"minScore\"","\"minScoreOrder\"",\
    "\"simpleMajorName\"","\"majorNameDesc\"","\"simplifySpecialCourse\"",\
    "\"specialCourse\"","\"majorGroup\""]

schoolPlanFieldList=["major_name","province",\
					 "curriculum","category","year",\
					 "batch_name","enroll_num","tuition","lengthOfSchooling","selectSubjects"]

# ======获取高校信息
def getSchoolList(pageno):
	url=schoolListUrl+"pn="+str(pageno)
	# print(url)
	# print(pageno)
	response=requests.get(url)
	# print(response)
	respText=response.text
	# print(respText)
	respJson=json.loads(respText)
	# print(respJson["status"])
	
	# print(respJson["data"]["ranking"]["tRow"][0]["college_name"])
	return respJson["data"]["ranking"]["tRow"]

# 更新所有学校信息
def getAllSchool():

	# deleteAllSchool()

	bFlag=True
	# pageno=1
	pageno=1
	count=0
	while(bFlag):
		data=getSchoolList(pageno)
		if len(data)==0 :
			bFlag=False
		for key in range(len(data)):
			count=count+1

			# print(count,data[key]["college_name"])
			# print(data[key])
			insertSchool(data[key])

		print("第",pageno,"页")
		time.sleep(1)
		pageno=pageno+1

def deleteAllSchool():
	sqlstr="delete from college_info"
	dbconn=DBConn()
	dbconn.execSql(sqlstr)

def insertSchool(schoolInfo):
	# dbconn=DBConn()
	# print(schoolInfo["college_name"])

	sqlstr="insert into college_info("

	values="values("

	for num in schoolFieldList :
		fieldname=num.replace('\"','')
		if fieldname in schoolInfo:
			sqlstr=sqlstr+num+","
			if fieldname=='logourl'  :
				values=values+"'"+str(schoolInfo["logo"])+"',"
			else :
				values=values+"'"+str(schoolInfo[fieldname]).replace('\'','\'\'')+"',"
				
	# print(sqlstr)
	sqlstr=sqlstr+"logourl,"
	values=values+"'"+str(schoolInfo["logo"])+"',"
	# print(values)

    #下载图片文件并保存进数据库2022.12.20
	logoUrl=schoolInfo["logo"]
	a=urlparse(logoUrl)
	file_path=a.path
	filename=os.path.basename(a.path)
	urllib.request.urlretrieve(logoUrl,filename=filename)
	
    # 打开图片编码成base64的字节码后存入
	jpg_byte=None
	content=None
	with open(filename,'rb') as f:
		jpg_byte=f.read()
		content=base64.b64encode(jpg_byte)

	#删除文件
	os.remove(filename)

    #插入数据库
	#==================================
	try:
		sqlstr=sqlstr[0:len(sqlstr)-1]+")\n"+values[0:len(values)-1]+")"
		dbconn=DBConn()
		dbconn.execSql(sqlstr)
	except Exception as e:
		print(sqlstr)
		raise e
	
    #更新数据库logo
	college_name=schoolInfo["college_name"]
	sqlstr1="update college_info set logo=? where college_name=?"
	dbconn=DBConn()
	dbconn.conn.execute(sqlstr1,(content,college_name))
	dbconn.conn.commit()

	print(schoolInfo["college_name"],"数据更新完成")
	
def getAllSchoolName():
	sqlstr="select college_name from college_info order by id limit 100 offset 2900"

	dbconn=DBConn()
	schools=dbconn.execQuery(sqlstr)

	return schools

	
# ===========================
# 录取分数线
def getScore(college_name,province,year):
	url=schoolScoreUrl+"school="+str(college_name)+"&province="+str(province)+"&year="+str(year)
	print(url)
	response=requests.get(url)
	respText=response.text
	# print(respText)
	respJson=json.loads(respText)
	retJson=None
	try:
		retJson=respJson["data"]["school_score"]["dataList"]
	except Exception as e:
		print(e)
		print(respJson)
		return None
	
	return retJson

def deleteAllSchoolScore():
	sqlstr="delete from schoolscore"
	dbconn=DBConn()
	dbconn.execSql(sqlstr)

# 获取学校分数线
def insertSchoolScore():
	deleteAllSchoolScore()

	schoolNames=getAllSchoolName()

	startTime=datetime.now()

	# 更新2020-2024年各高校录取分数线数据
	count=0
	for schoolName in schoolNames:
		year=2024
		while year>2019 :
			schoolscores=getScore(schoolName[0],"浙江",year)
			if schoolscores==None :
				year=year-1
				continue
			# print(schoolscores)
			for schoolscore in schoolscores :

				sqlstr="insert into schoolscore("

				values="values("

				if schoolscore['year']==str(year):
					#插入数据库
					for num in schoolScoreFieldList :
						fieldname=num.replace('\"','')
						if fieldname in schoolscore:
							sqlstr=sqlstr+num+","
							values=values+"'"+str(schoolscore[fieldname]).replace('\'','\'\'')+"',"
				sqlstr=sqlstr[0:len(sqlstr)-1]+")\n"+values[0:len(values)-1]+")"
				count=count+1
				#插入数据库
				# print(sqlstr,"\n")
				print(count)
				# if count%100 == 0 :
				# 	print("已更新：",count,"\n")
				dbconn=DBConn()
				dbconn.execSql(sqlstr)
				# print(schoolscore,"\n")
				# print(sqlstr,"\n")

			year=year-1
	endTime=datetime.now()
	print("已更新",count,"条高校录取分数线，耗时：",(endTime-startTime),"\n")

#================================================================
# 获取专业分数线
def getMajorScore(college_name,province,year):
	url=schoolMajorScoreUrl+"school="+str(college_name)+"&province="+str(province)+"&year="+str(year)

	bFlag=True
	pn=1
	# delMajorScore(college_name,province)

	while bFlag :
		response=requests.get(url+"&pn="+str(pn))
		print(url+"&pn="+str(pn))
		pn=pn+1
		respText=response.text
		# print(respText)
		respJson=json.loads(respText)
		print(url)
		majorscores=None
		try:
			if respJson["errno"]!=0:
				break

			majorscores=respJson["data"]["major_score"]["dataList"]

		# print(majorscores)

			if len(majorscores)<=0 :
				bFlag=False
			else:
				if majorscores[0]["year"]!=str(year) :
					bFlag=False
				else:
					for majorscore in majorscores :
						# insertMajorScore(majorscore)
						print(majorscore)
					print(college_name,"-",province,"-",year,"-","查询成功！")
		except:
			bFlag=False
			print(college_name,"-",province,"-",year,"-","查询出错！")
			
def delMajorScore(college_name,province):
	sqlstr="delete from majorscore where \"legalName\"='"+college_name+"' and province='"+province+"'"
	dbconn=DBConn()
	dbconn.execSql(sqlstr)
	

def delAllMajorScore():
	sqlstr="delete from majorscore "
	dbconn=DBConn()
	dbconn.execSql(sqlstr)
	
    # 插入数据库
def insertMajorScore(majorscore):
	# print(majorscore)
	sqlstr="insert into majorscore("

	values="values("

	for num in schoolMajorScoreFieldList :
		fieldname=num.replace('\"','')
		
		if fieldname in majorscore:
			sqlstr=sqlstr+num+","
			
			values=values+"'"+str(majorscore[fieldname]).replace('\'','\'\'')+"',"

	sqlstr=sqlstr[0:len(sqlstr)-1]+")\n"+values[0:len(values)-1]+")"
	# print(sqlstr)
	dbconn=DBConn()
	dbconn.execSql(sqlstr)
	
#近5年的专业成绩,默认5个线程执行
def getMajorScoreNear5(college_name,province):
	year=2024
	while year>=2019:
		getMajorScore(college_name,province,str(year))
		year=year-1

def getMajorScoreNear5s(college_names,province,threadno):

	for college_name in college_names:
		print("线程",threadno,college_name,province)
		getMajorScoreNear5(college_name,province)

# 大学名字、省份、线程数
def getMajorScoreNear5Byhread(province,threadnum=5):
	#获取所有大学清单
	schoolNames=getAllSchoolName()
	schoolNameList=[]
	i=0
	while i<threadnum:
		schoolNameList.append([])
		i=i+1
	threadingList=[]

	index=0
	count=len(schoolNames)
	for schoolName in schoolNames:
		schoolNameList[index % threadnum].append(schoolName[0])
		index=index+1


	i=0
	while i<threadnum:
		threadingList.append(threading.Thread(target=getMajorScoreNear5s,args=(schoolNameList[i],province,i)))
		print(schoolNameList[i])
		i=i+1

	#启动线程
	i=0
	while i<threadnum:
		threadingList[i].start()
		i=i+1

#================================================================
# 获取学校招生计划
def getCollegePlanFromUrl(school,province,year,pn,rn):
	# 参数pn-第几条记录开始，query-中文学校名，province-省，year-年份,curriculum-课程类型,3+3综合,rn-每页记录数
	
	url=schoolPlanUrl+"&query="+school+"&province="+province+"&year="+str(year)+"&pn="+str(pn)+"&rn="+str(rn)
	try:
		response=requests.get(url)
		respText=response.text
		respJson=json.loads(respText)
		ret=respJson["data"]["list"]
		# print(respText)
		return ret
	except:
		print(url)
		return None
	

# 插入招生计划数据库
def insertCollegePlan(collegePlan,schoolName):
	sqlstr="insert into college_plan(legalName,"

	values="values('"+schoolName+"',"

	for num in schoolPlanFieldList :
		fieldname=num.replace('\"','')
		
		if fieldname in collegePlan:
			sqlstr=sqlstr+num+","
			
			values=values+"'"+str(collegePlan[fieldname]).replace('\'','\'\'')+"',"

	sqlstr=sqlstr[0:len(sqlstr)-1]+")\n"+values[0:len(values)-1]+")"
	# print(sqlstr)
	dbconn=DBConn()
	dbconn.execSql(sqlstr)
	
def getCollegePlan():
	#获取所有大学清单
	schoolNames=getAllSchoolName()
	
	for schoolName in schoolNames:
		province="浙江"
		year=2024
		while year>2019 :
			rn=50
			pn=0
			flag=True
			while flag :
				collegePlans=getCollegePlanFromUrl(schoolName[0],province,year,pn,rn)
				if collegePlans==None or len(collegePlans)<=0 :
					flag=False
				else:
					for collegePlan in collegePlans :
						# print(collegePlan)
						insertCollegePlan(collegePlan,schoolName[0])
					print(schoolName[0],"-",province,"-",year,"-","查询成功！")
					pn=pn+rn
			year=year-1
		

# insertSchoolScore()
# getAllSchool()
# print(getSchoolList(1))
# getMajorScoreNear5Byhread("浙江")
getMajorScore("宁波大学","浙江",2024)
# getMajorScoreNear5Byhread("浙江")
# getCollegePlanFromUrl("浙江大学","浙江","2024","22","10")
# getCollegePlan()