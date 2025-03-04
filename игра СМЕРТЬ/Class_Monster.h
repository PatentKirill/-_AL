#pragma once
#include <unordered_map>




class Monster: public Living_Object
{
protected:
	std::string picture;
	
	struct DialogueNode {
		std::string text;
		std::vector<std::pair<std::string, int>> options;
	};
	std::unordered_map<int, DialogueNode> nodes;

public:
	Monster(char sign, ConsoleColor text, ConsoleColor baground, int max_HP, int Damage, int Defence, Object* ob, std::string picture, std::string name): 
	Living_Object(sign, text, baground, max_HP, Damage, Defence, true, ob, name), picture{picture}
	{}
	virtual ~Monster()
	{}
	Monster(): Living_Object()
	{ }
	void dialog()
	{
		int nodeId = 0;
		std::vector<std::string> dialogueHistory;

		while (nodeId != -1) {
			

			DialogueNode& node = nodes[nodeId];
			std::cout << name << ": " << node.text << "\n";

			if (node.options.empty()) {
				std::cout << "ƒиалог завершЄн.\n";
				break;
			}

			for (size_t i = 0; i < node.options.size(); ++i) {
				std::cout << i + 1 << ". " << node.options[i].first << "\n";
			}

			char choice;
			do {
				choice = _getch();
			} while (choice < '1' || choice > '0' + node.options.size());

			int index = choice - '1';
			dialogueHistory.push_back(node.text); // —охран€ем фразу монстра
			dialogueHistory.push_back("> " + node.options[index].first); // —охран€ем ответ игрока

			nodeId = node.options[index].second;
			system("cls"); // ќчистка экрана
			print_Monster();
			for (const auto& line : dialogueHistory) {
				std::cout << line << "\n"; // ¬ывод всей истории
			}
		}
	}
	virtual void action()
	{}
	bool prov_i_g(int i, int g)
	{
		return (i == this->i && g == this->g);
	}
	void print_Monster()
	{
		//system("cls");
		
		std::ifstream file(picture); // ќткрываем файл
		if (!file) {
			std::cerr << "ќшибка: не удалось открыть файл!\n";
			file.close();
		}
		else
		{
			std::string line;
			std::cout << name << ":\n" << "HP:  " << max_HP << '/' << HP << "\tDamage:  " << damage << "\tDefence:  " << defence << '\n';
			while (std::getline(file, line)) 
			{ 
				std::cout << line << std::endl;
			}
		}
		std::cout << "\033[0m" << std::endl;

		file.close();
	}
	
};

class Zmei: public Monster
{
public:
	Zmei(Object* base): Monster('~', Green, Black, 20, 2, 3, base, "ascii_art_snake.txt", "—трашна€ «ћ≈я")
	{
		nodes[0] = { "ѕ—сс——", {{"“ы умеешь говорить?", 2}, {"продолжить бой", -1}, {"ѕспс—ѕс", 1} }};
		nodes[1] = { "«ме€ смотрит на вас, как на сумасшедшего", {{"Ћадно...", -1}} };
		nodes[2] = { "ѕсп—ѕспс—б", { {"¬идимо нет", -1} } };
	}
};

