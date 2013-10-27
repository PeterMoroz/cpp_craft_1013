#include <reader.h>
#include <map>
#include <list>

int main()
{
	binary_reader::Reader reader(std::string(SOURCE_DIR) + "/input.txt");
	std::ofstream outputFile(SOURCE_DIR "/output.txt" );
	
	unsigned __int32 commonCountTime = 1;
	unsigned __int32 countCurrentTime = 1;
	std::map <unsigned __int32, std::list <unsigned __int32> > countOfType;
	std::map <unsigned __int32, std::list <unsigned __int32> >::iterator it;
	unsigned __int32 currentTime = 0;
	
	if (reader.isOpenedFile())
	{
		MessageData messageData;
		bool isFirst = true;
		while (reader.readMessageData(&messageData))
		{
			if (isFirst)
			{
				currentTime = messageData.time;
				isFirst = false;
			}

			if (messageData.time != currentTime)
			{
				countCurrentTime = 1;
				++commonCountTime;
				currentTime = messageData.time;
			} else
			{
				++countCurrentTime;
			}

			if ((it = countOfType.find(messageData.type)) == countOfType.end())
			{
				std::list <unsigned __int32> listLenght;
				listLenght.push_back(messageData.len);
				countOfType.insert(std::pair<unsigned __int32, std::list <unsigned __int32> >(messageData.type, listLenght));
			}
			else
			{
				unsigned __int32 commonLenghtMessage = 0;
				for (std::list <unsigned __int32>::reverse_iterator i = it->second.rbegin(); 
					i != it->second.rend() && countCurrentTime > 1;
					++i, --countCurrentTime)
				{
					commonLenghtMessage += *i;
				}
				commonLenghtMessage += messageData.len;
				if (commonLenghtMessage < 2048)
				{
					it->second.push_back(messageData.len);
					break;
				}
			}
		}
		for (it = countOfType.begin(); it != countOfType.end(); ++it)
		{
			unsigned __int32 type = it->first;
			outputFile.write(reinterpret_cast<char*>(&type), sizeof(unsigned __int32));
			double mean = (double)it->second.size() / commonCountTime;
			outputFile.write(reinterpret_cast<char*>(&mean), sizeof(double));
			//outputFile << type << " " << mean << std::endl;
		}
	}
	outputFile.close();
}

