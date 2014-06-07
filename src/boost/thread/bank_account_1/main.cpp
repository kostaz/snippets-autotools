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
		mutex.lock();
		balance += amount;
		mutex.unlock();
	}

	void Withdraw(int amount)
	{
		mutex.lock();
		balance -= amount;
		mutex.unlock();
	}

	int GetBalance()
	{
		mutex.lock();
		int b = balance;
		mutex.unlock();

		return b;		
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

