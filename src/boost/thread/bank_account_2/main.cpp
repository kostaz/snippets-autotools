#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

class BankAccount
{
private:
	boost::mutex mutex;
	int balance;
public:
	void Deposit(int amount)
	{
		boost::lock_guard<boost::mutex> guard(mutex);
		balance += amount;
	}

	void Withdraw(int amount)
	{
		boost::lock_guard<boost::mutex> guard(mutex);
		balance -= amount;
	}

	int GetBalance()
	{
		boost::lock_guard<boost::mutex> guard(mutex);
		return balance;
	}
};

BankAccount JoesAccount;

void Deposit()
{
	for (int i = 0; i < 1000; i++) {
		std::cout << ".";
		JoesAccount.Deposit(1000);
	}
}

void Withdraw()
{
	for (int i = 0; i < 1000; i++) {
		std::cout << "W";
		JoesAccount.Withdraw(100);
	}
}

int main()
{
	boost::thread th_deposit(Deposit);
	boost::thread th_withdraw(Withdraw);

	th_deposit.join();
	th_withdraw.join();	

	return 0;
}

