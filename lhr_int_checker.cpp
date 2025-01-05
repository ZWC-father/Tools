#include "Fraction.hpp"
#include "boost/multiprecision/cpp_int.hpp"
#include <ctime>
#include <csignal>
#include <chrono>
#include <thread>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
bool running = 1;
int lim_a, lim_b, count, interval;

void sig_handler(int signal){
	if(running){
		std::cout << "\nPress Ctrl+C Again to Exit\n" << std::endl;
		running = 0;
	}else{
		exit(0);
	}
}

void gen_log(const std::string& a, const std::string& b, const std::ostringstream& c1, const std::ostringstream& c2){
	std::ofstream ofs("Data.in");
	ofs << a << '\n' << b << std::endl;
	ofs.close(), ofs.open("LHR.out");
	ofs << c1.str() << std::endl;
	ofs.close(), ofs.open("Boost.out");
	ofs << c2.str() << std::endl;
	ofs.close();
}

void lhr_calc(const Int& lhr_a, const Int& lhr_b, std::ostringstream& c1, bool opt){
	auto start = std::chrono::high_resolution_clock::now();
	Int lhr_c;
	if(opt)lhr_c = lhr_a / lhr_b;
	else lhr_c = lhr_a * lhr_b;
	auto end = std::chrono::high_resolution_clock::now();
	
	c1 << lhr_c;
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "LHR a" << (opt ? '/' : '*') << "b Used Time: " << duration.count() << " ms" << std::endl;
}

void boost_calc(const boost::multiprecision::cpp_int& boost_a, const boost::multiprecision::cpp_int& boost_b,
		std::ostringstream& c2, bool opt){
	auto start = std::chrono::high_resolution_clock::now();
	boost::multiprecision::cpp_int boost_c;
	if(opt)boost_c = boost_a / boost_b;
	else boost_c = boost_a * boost_b;
	auto end = std::chrono::high_resolution_clock::now();
	
	c2 << boost_c;
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Boost a" << (opt ? '/' : '*') << "b Used Time: " << duration.count() << " ms" << std::endl;

}

int main(int argc, char **argv){
	if(argc != 5)throw std::runtime_error("Please Provide 4 Args: [a_limit] [b_limit] [count] [interval_in_ms]");
	try{
		lim_a = std::stoi(std::string(argv[1]));
		lim_b = std::stoi(std::string(argv[2]));
		count = std::stoi(std::string(argv[3]));
		interval = std::stoi(std::string(argv[4]));
		if(lim_a <= 0 || lim_b <= 0 || count <= 0 || interval < 0)throw::std::runtime_error("Invalid Args");
	}catch (const std::exception &e){
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::mt19937 rnd(time(0));
	std::uniform_int_distribution<int> range_a(1, lim_a), range_b(1, lim_b);
	std::uniform_int_distribution<int> range_digit('0', '9');
	std::cout << "Start Testing..." << std::endl;
	std::signal(SIGINT, sig_handler);

	for(int i = 0; i < count; i++){
		std::cout << "Start Round #" << i + 1 << std::endl;
		int len_a = range_a(rnd);
		int len_b = range_b(rnd);
		std::string a = std::to_string(range_digit(rnd));
		std::string b = std::to_string(range_digit(rnd));
		std::ostringstream c1, c2;
		while(a[0] == '0')a[0] = range_digit(rnd);
		while(b[0] == '0')b[0] = range_digit(rnd);
		for(int j = 1; j < len_a; j++)a += range_digit(rnd);
		for(int j = 1; j < len_b; j++)b += range_digit(rnd);

		Int lhr_a, lhr_b;
		std::istringstream iss_a(a), iss_b(b);
		iss_a >> lhr_a, iss_b >> lhr_b;
		lhr_calc(lhr_a, lhr_b, c1, 0);
		boost::multiprecision::cpp_int boost_a(a), boost_b(b);
		boost_calc(boost_a, boost_b, c2, 0);
		
		if(c1.str() != c2.str()){
			std::cout << "(a*b) Product Not Match (YJX_AK_IOI)" << std::endl;
			std::cout << "Refer to Data.in/LHR.out/Boost.out for Detail" << std::endl;
			gen_log(a, b, c1, c2);
			return 2;
		}

		c1.clear(), c2.clear();

		lhr_calc(lhr_a, lhr_b, c1, 1);
		boost_calc(boost_a, boost_b, c2, 1);

		if(c1.str() != c2.str()){
			std::cout << "(a/b) Product Not Match (WTY_AK_IOI)" << std::endl;
			std::cout << "Refer to Data.in/LHR.out/Boost.out for Detail" << std::endl;
			gen_log(a, b, c1, c2);
			return 3;
		}
		
		if(i != count - 1){
			std::cout << "Sleeping...\n" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
	}

	return 0;
}
