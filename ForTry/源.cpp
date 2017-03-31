#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <queue>
#include <Windows.h>
#include <stdlib.h>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

class str2
{
public:
	string s1;
	string s2;
};

int main1() {
	ifstream in("C:\\Users\\lining\\Desktop\\a.txt");
	if (!in.is_open()) {
		cout << "error" << endl;
		exit(1);
	}
	int n;
	in >> n; 
	map<string, int> M;
	vector<str2> Q;
	int g = 0;
	for (int i = 0; i < n; i++) {

		string s1, s2;
		in >> s1 >> s2;
		str2 s;
		s.s1 = s1;
		s.s2 = s2;
		Q.push_back(s);
		if (M.find(s1) == M.end()) {
			M[s1] = g++;
		}
		if (M.find(s2) == M.end()) {
			M[s2] = g++;
		}
	}
	in.close();
	ofstream out("C:\\Users\\lining\\Desktop\\b.txt");
	for (map<string, int>::iterator  i = M.begin(); i != M.end(); i++) {
		out << "INSERT INTO label VALUES(" << i->second + 1 << ",'" << i->first.substr(0,1) << "');" << endl;
	}
	for (vector<str2>::iterator i = Q.begin(); i != Q.end(); i++) {
		out << "INSERT INTO graph VALUES(" << M[(*i).s1]+1 << "," << M[(*i).s2]+1 << ");" << endl;
		out << "INSERT INTO graph VALUES(" << M[(*i).s2] + 1 << "," << M[(*i).s1] + 1 << ");" << endl;
	}
	system("pause");
	out.close();
	return 0;
}
int main(void) {
	string q1[4];
	q1[0] = "b";
	q1[1] = "a";
	q1[2] = "e";
	q1[3] = "c";
	string q2[3];
	q2[0] = "e";
	q2[1] = "a";
	q2[2] = "d";
	string q3[2];
	q3[0] = "c";
	q3[1] = "d";
	const int querynum = 3;
	int num[querynum] = { 4,3,2 };

	string* Q[3] = { q1,q2,q3 };
	ofstream out("C:\\Users\\lining\\Desktop\\b.txt");

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		/* Create a connection */
		//driver = get_driver_instance();
		//con = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
		/* Connect to the MySQL graphengine database */
		//con->setSchema("graphengine");
		//stmt = con->createStatement();
/*		stmt->execute(
		"drop table if exists ttt;\
		create table ttt(\
			node1 int,\
			node2 int,\
			label varchar(10)\
		);\
		drop table if exists q1;\
		drop table if exists q2;\
		drop table if exists q3;\
		create table q1(\
			b int,\
			a int,\
			e int,\
			c int\
		);\
		create table q2(\
			e int,\
			a int,\
			b int\
		);\
		create table q3(\
			c int,\
			d int\
		); ");
		//delete stmt;
		/* '?' is the supported placeholder syntax */
		for (int i = 0; i<querynum; i++){
			string sa =
				"insert into ttt\
					select *\
					from(select node1, node2, label\
						from(select graph.node1, graph.node2\
							from(select node\
								from label\
				where label = '(?)' 		#here need the c#\
					)as ta\
							inner join graph\
					on ta.node = graph.node1\
					)as tb\
						inner join label\
					on tb.node2 = label.node order by node\
					)as tc\
				where tc.label in(";
			string sb;
			for (int j = 0; j < num[i]; j++) {
				sb += "'";
				sb += Q[i][j];
				sb += "'";
				if (j != num[i] -1 ) sb += ",";
				else sb += ");";
			}
			out << sa + sb << endl;
			//pstmt = con->prepareStatement(sa+sb);
			//pstmt->setString(1, Q[i][0]);
			//pstmt->executeQuery();
		}
		//delete pstmt;
	}catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line "
			<< __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() <<
			" )" << endl;
	}
	out.close();
	system("pause");
	return 0;
}