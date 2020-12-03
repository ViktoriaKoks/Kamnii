#include <iostream>
#include <string>
#include <random>
#include <sstream>
std::random_device rd;
std::ranlux48 rnd { rd() };
std::uniform_int_distribution<> dist1 {15, 25};
std::uniform_int_distribution<> dist2 {1, 3};
int read_answer()
{
    int result;
    std::cout <<"Сколько камушков ты хочешь взять: 1,2 или 3?" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::stringstream input_ss { input };
    input_ss >> result;
    bool f = input_ss.fail();
    while ( f || result < 1 || result > 3) {
        std::cerr << "ОТ 1 ДО 3! Зачем ты взял больше?. Еще раз: " << std::endl;
    	std::getline(std::cin, input);
    	std::stringstream input_ss { input };
        input_ss >> result;
        f = input_ss.fail();
    }
    return result;
}
int lvl_1(bool f)
{
	int d1 = dist1(rnd);
	std::cout << "Имеется " << d1 << " камушков" << std::endl;
	int d2, a;
	bool f1;
	for (unsigned i=0; d1>0; ++i)
	{
		if( i%2 == 0 )
	    {
	        a = read_answer();
	        while (a > d1)
	        {
	        	std::cerr << "Осталось " << d1 << " камушков. Сделай другой выбор!" << std::endl;
	        	a = read_answer();
	        }
	        std::cout << "Осталось " <<(d1 - a) <<" камушков " << std::endl;
	        d1 -= a;
	        f1 = true;
	    }
	    else
	    {
	    	d2 = dist2 (rnd);
	    	while (d2 > d1)
	    	{
	    		d2 = dist2 (rnd);
	    	}
	        std::cout << "Компьютер взял камушков - " << d2 << ". Камушков осталось: " << (d1-d2) << std::endl;
	        d1 -= d2;
	        f1 = false;
	    }
			if (d1 < 13 and f) return d1;
	    }
	if(f1) std::cout << "GAME OVER. Ты проиграл." << std::endl;
	else std::cout << "GAME OVER. Ты победил! Ехуу" << std::endl;
	return 1;
}
void lvl_3(bool f, int ans)
{
	int d1 = ans;
	std::cout << "Имеется " << d1 << " камушков" << std::endl;
	int d2, a;
	bool f1;
	for (unsigned i=0; d1>0; ++i)
	{
		if(i%2 == 0)
	    {
	        a = read_answer();
	        while (a > d1)
	        {
	        	std::cerr << "Осталось " << d1 << " камушков. Сделай другой выбор!";
	        	a = read_answer();
	        }
	        std::cout << "Осталось " <<(d1 - a) <<" камушков " << std::endl;
	        d1 -= a;
	        f1 = true;
	    }
	    else
	    {
	        if( (d1 - 9) % 4 == 1 or d1 - 9 == -3 or d1 == 2 )
			{
	    		d1 -= 1;
	    		std::cout << "Компьютер взял камушков - 1" << ". Камушков осталось: " << d1 << std::endl;
	    	}

	    	else if( (d1 - 9) % 4 == 2 or d1 - 9 == -2 or d1 == 3 )
	    	{
	    		d1 -= 2;
	    		std::cout << "Компьютер взял камушков - 2" << ". Камушков осталось: " << d1 << std::endl;
	    	}

	    	else if( (d1 - 9) % 4 == 3 or d1 - 9 == -1 or d1 == 4 )
	    	{
	    		d1 -= 3;
	    		std::cout << "Компьютер взял камушков - 3" << ". Камушков осталось: " << d1 << std::endl;
	    	}
	    	else
	    	{
	    		d2 = dist2 (rnd);
	    		while (d2 > d1)
	    		{
	    			d2 = dist2 (rnd);
	    		}
	    		d1 -= d2;
	    		std::cout << "Рандомный выбор - " << d2 << ". Камушков осталось: " << d1 << std::endl;
	    	}
	    	f1 = false;
	    }
	}
	if(f1) std::cout << "GAME OVER. Ты проиграл" << std::endl;
	else std::cout << "GAME OVER. Ты победил! Ехуу" << std::endl;
}
void lvl_2()
{
	bool f = true;
	int ans = lvl_1(f);
	lvl_3(f, ans);
}
int main()
{
	int choise;
	bool f = false;
	do
	{
		std::cout << "Какой уровень сложности игры ты предпочитаешь? : " << std::endl
				  << "1. Легкая игра" << std::endl
				  << "2. Сложная игра" << std::endl
			      << "3. Очень сложная игра" << std::endl
				  << "4. Завершить игру" << std::endl;
		std::cin >> choise;
		while (std::cin.fail() or choise < 1 or choise > 4)
		    {
				std::cerr << "Непонятно... Попробуй еще раз :" << std::endl;
		        if (std::cin.fail())
		        {
		            std::cin.clear();
		            std::cin.ignore(32767,'\n'); //
		        }
		        std::cin >> choise;
		    }
		std::cin.ignore(32767,'\n');
		switch(choise){
			case 1: {lvl_1(f); break;}
			case 2:	{lvl_2(); break;}
			case 3:	{lvl_3(f, dist1(rnd)); break;}
		}
	}while (choise != 4);
    return 0;
}
