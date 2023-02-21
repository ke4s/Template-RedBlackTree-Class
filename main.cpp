

#include "RedBlackTree.hpp"
#include "map"

int	main()
{
	RedBlackTree<int, int, std::greater<int> > temp;
	std::map<int,int, std::greater<int> > orj;


	temp.insert(12,1);
	temp.insert(5,1);
	temp.insert(16,1);
	temp.insert(8,1);
	temp.insert(9,1);
	temp.insert(10,1);

	orj.insert(std::pair<int, int>(12,1));

	orj.insert(std::pair<int, int>(5,1));
	orj.insert(std::pair<int, int>(16,1));
	orj.insert(std::pair<int, int>(8,1));
	orj.insert(std::pair<int, int>(9,1));
	orj.insert(std::pair<int, int>(10,1));

	//10 20 0 15 17 40 50 60
	//12 5 16
	++orj.begin();

	std::map<int, int, std::greater<int> >::iterator it = orj.begin();
	std::cout << "***************************\n";
	std::cout << it->first << "\n";

	std::cout << (++it)->first << "\n";
	std::cout << (++it)->first << "\n";

	std::cout << "***************************\n";

	std::cout <<  orj.begin()->first << "\n";
	std::cout << "***************************\n";
	std::cout <<temp.getBigger(temp.getBigger(temp.search(5)))->key << "\n";
	std::cout <<temp.getBigger(temp.getBigger(temp.getBigger(temp.search(5))))->key << "\n";
	std::cout <<temp.getBigger(temp.getBigger(temp.getBigger(temp.getBigger(temp.search(5)))))->key << "\n";
	std::cout <<temp.getBigger(temp.getBigger(temp.getBigger(temp.getBigger(temp.getBigger(temp.search(5))))))->key << "\n";
	std::cout <<temp.getBigger(temp.getBigger(temp.getBigger(temp.getBigger(temp.getBigger(temp.getBigger(temp.search(5)))))))->key << "\n";


	system("leaks a.out");
}
//begin sol uç

//++ operatörü keyin sayısal değerinin bir büyüğüne bakar