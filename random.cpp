/*
	Copyright(c) @doubleki 2022-2022
	All Rights Reserved.

	This file was created by doubleki at 2022/10/01 19:48
	Updated 1.0.0 version at 2022/10/01 21:15
	This cpp file can run as a random decitrator
*/
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

class Student
{
  private:
	int id;
	std::string name;
	bool isvis;

  public:
	Student(int id_ = -1, std::string name_ = "Null", bool isvis_ = false) : id(id_), name(name_), isvis(isvis_)
	{
		//noting
	}
	bool is_Visted();
	std::string Student_Name();
	bool clear();
	bool Vis();
};
bool Student::Vis()
{
	isvis = true;
	return true;
}
bool Student::is_Visted()
{
	return isvis;
}
std::string Student::Student_Name()
{
	return name;
}
bool Student::clear()
{
	isvis = false;
	return isvis;
}
int rand_int(int begin,int end)  //左开右闭区间
{
	int res;
	time_t temp=time(NULL);
	res=temp%(begin-end);
	res=res+begin;
	return res;
}
bool print_time_to_log()
{
	time_t temp = time(NULL);
	struct tm *local_time;
	local_time = std::localtime(&temp);
	std::ofstream logoutput("random.log", std::ios::app);
	char tm_ptr[100];
	std::strftime(tm_ptr, 100, "%F %T  ", local_time);
	std::string res = tm_ptr;
	logoutput << res;
	/*	logoutput<<local_time->tm_year
	                 <<"-"
	                 <<local_time->tm_mon
	                 <<"-"
	                 <<local_time->tm_mday
	                 <<" "
	                 <<local_time->tm_hour
	                 <<":"
	                 <<local_time->tm_min
	                 <<":"
	                 <<local_time->tm_sec
	                 <<"  ";
	                 */
	return true;
}
std::vector<Student> init(std::vector<Student> &student)
{
	std::ofstream logoutput("random.log", std::ios::app);
	student.clear();
	std::ifstream input("input.txt");
	std::string name_temp;
	int id = 1;
	while (input >> name_temp)
	{
		Student temp(id, name_temp, false);
		student.push_back(temp);
		id++;
	}
	print_time_to_log();
	logoutput << "Successfully init()\n";
	return student;
}
bool random_decitrader(std::vector<Student> &student)
{
	std::ofstream logoutput("random.log", std::ios::app);
	if (student.empty())
	{
		print_time_to_log();
		logoutput << "Error 101:No student!\n";
		return false;
	}
	int len = student.size();
	bool isEmpty;
	isEmpty = true;
	for (int i = 0; i < len; i++)
	{
		if (student[i].is_Visted() == false)
		{
			isEmpty = false;
			break;
		}
	}
	if (isEmpty == true)
	{
		print_time_to_log();
		logoutput << "Error102:No student!\n";
		std::cout << "所有学生都被抽取过了！请清空待抽取名单！\n";
		return false;
	}
	std::srand(std::time(0));
	while (true)
	{
		int id_temp = rand_int(0,len);
		if (student[id_temp].is_Visted() == true)
		{
			continue;
		}
		else
		{
			std::cout << student[id_temp].Student_Name();
			std::cout << std::endl;
			student[id_temp].Vis();
			print_time_to_log();
			logoutput << "Successfully get a student " << student[id_temp].Student_Name() << std::endl;
			break;
		}
	}
	return true;
}
int main()
{
	std::vector<Student> student;
	init(student);
	int len = student.size();
	char temp;
	while (true)
	{
		//std::getline(std::cin, temp);
		if (kbhit())
		{
			temp=getch();
			if (temp =='c')
			{
				for (int i = 0; i < len; i++)
				{
					student[i].clear();
				}
				std::cout << "清空成功！\n";
				std::ofstream logoutput("random.log", std::ios::app);
				print_time_to_log();
				logoutput << "Successfully clear\n";
			}
			else
			{
				random_decitrader(student);
			}
		}
	}
	return 0;
}
