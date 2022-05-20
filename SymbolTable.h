#include<iostream>
#include<string.h>

using namespace std;

struct SymbolTableData
{
	string id;
	string value;
	int address;
};



class SymbolTable
{
private:
	SymbolTableData* m_table = nullptr;
	int m_size;
	int m_current_address;
public:
	SymbolTable()
	{
		m_table = new SymbolTableData[100];
		m_size = 0;
		m_current_address = 0;
	}

	int serach(string id)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (m_table[i].id == id)
			{
				return i;
			}
		}

		return -1;
	}

	void insert(string id, string value, string type)
	{
		if (this->serach(id) == -1)
		{
			m_table[m_size].id = id;
			m_table[m_size].value = value;
			if (type == "int")
			{
				m_table[m_size].address = m_current_address;
				m_current_address += 4;
			}
			else if (type == "char")
			{
				m_table[m_size].address = m_current_address;
				m_current_address += 1;

			}
			m_size++;
		}
		
	}

	void print()
	{
		for (int i = 0; i < m_size; i++)
		{
			cout << m_table[i].id << " " << m_table[i].value << " " << m_table[i].address << endl;
		}
	}

	~SymbolTable()
	{
		delete [] m_table;
	}
};