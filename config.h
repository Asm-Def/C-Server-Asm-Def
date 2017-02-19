#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <cstdio>
#include <string>
#include <cstring>
#include <map>

short port = 10240;	//0~65535

namespace config
{
	using namespace std;
	enum tp{ STRING, INT };

	struct data
	{
		tp type;
		struct{
			string str;
			int x_32;
		} val;
	};

	map<string, data> conf;

	inline FILE *Fopen()
	{
		FILE *config = fopen("server.conf", "r");
		if(config == NULL)
		{
			config = fopen("server.conf", "w+");
			map<string, data>::iterator it;
			for(it = conf.begin();it != conf.end();++it)
			{
				fprintf(config, "%s\t\t", (*it).first.c_str());
				switch((*it).second.type)
				{
					case STRING:fprintf(config, "%s\n", (*it).second.val.str.c_str());break;
					case INT:fprintf(config, "%d\n", (*it).second.val.x_32);break;
				}

			}
		}
		return config;
	}
}

inline void get_config()
{
	config::data &d = config::conf["port"]; d.type = config::INT; d.val.x_32 = port;

	FILE *in = config::Fopen();
/*
 * other profiles
 */
	char str[100], *it = str;
	int ch, i;
	while(fscanf(in, "%*[^a-zA-Z_]*%[a-zA-Z_]", str) > 0)
	{
		config::data &val = config::conf[str];
		switch(val.type)
		{
			case config::STRING:
				if(fscanf(in, "%*[^a-zA-Z_]%[a-zA-Z_]", str) > 0)
					val.val.str = str;
				break;
			case config::INT:
				if(fscanf(in, "%d", &val.val.x_32) > 0);
				break;
		}
	}

	port = config::conf["port"].val.x_32;
}

#endif

