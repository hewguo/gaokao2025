# -*- coding: utf-8 -*-

import sqlite3


class DBConn :

	# dbname="gaokaodb"
	# user="gaokao"
	# password="gaokao"
	# host="127.0.0.1"
	# port="5432"

	conn=None

	def __init__(self):
		self.conn=sqlite3.connect("/Users/heweiguo/Downloads/gaokao2025/gaokao2025.sqlite")

	def execSql(self,sqlstr):
		curs=self.conn.cursor()

		curs.execute(sqlstr)

		self.conn.commit()

		curs.close()

	def execQuery(self,sqlstr):
		curs=self.conn.cursor()
		curs.execute(sqlstr)

		rows=curs.fetchall()

		curs.close()

		return rows


