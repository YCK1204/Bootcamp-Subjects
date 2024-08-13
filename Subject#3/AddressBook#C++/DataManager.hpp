#ifndef DATA_HPP
# define DATA_HPP

class DataManager
{
private:
	static DataManager* _instance;
	DataManager();
public:
	static DataManager& Instance();
	~DataManager();
	void Init();
};

#endif