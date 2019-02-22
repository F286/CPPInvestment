#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

const float inflation = 0.025;
//const float inflation = 0.04;

void CalculateReturn(string title, float startMoney, float monthlyContributionStart, float monthlyContributionEnd, float interestPerYear, int numberOfYears, float yearlyTax, float finalTax, float monthlyFee) {
	
	cout << fixed;
	cout << setprecision(0);
	
	cout << endl;
	cout << " — " << title << " — " << endl;
	cout << "Start Capital: $" << startMoney << endl;
	cout << "Monthly Contribution: $" << monthlyContributionStart << " to $" << monthlyContributionEnd << endl;
	cout << setprecision(1);
	cout << "Growth per Year: " << (interestPerYear - 1) * 100 << "%" << endl;
	cout << setprecision(0);
	cout << "Number of Years: " << numberOfYears << endl;
	cout << "Yearly Gains Tax: " << yearlyTax * 100 << "%" << endl;
	cout << "Final Gains Tax: " << finalTax * 100 << "%" << endl;
	cout << "Monthly Fee: $" << monthlyFee << endl;
	cout << endl;
	
	float interestPerMonth = pow(interestPerYear, 1.0 / 12.0);
	float totalMoney = startMoney;
	float totalInvested = startMoney;
	
	// Adjust contribution for inflation
	float currentCpi = 1.0;
	float monthlyInflation = pow(1.0 + inflation, 1.0 / 12.0);
	float cpiTotalInvested = startMoney;
	float finalCpi = pow(1.0 + inflation, numberOfYears);
	
	// Calculate returns
	for (int year = 0; year < numberOfYears; year++) {
		float startOfYearValue = totalMoney;
		float yearlyCapital = 0.0;
		float monthlyContribution = monthlyContributionStart + (monthlyContributionEnd - monthlyContributionStart) * ((currentCpi - 1) / (finalCpi - 1));
		
		if (year != 0 && year % 5 == 0) {
			cout << "Year " << year << ": $" << totalMoney << endl;
		}
		if (monthlyContributionStart != monthlyContributionEnd && year % 5 == 0) {
			cout << "Monthly Contribution " << year << ": $" << monthlyContribution << endl;
		}
		
	   for (int month = 0; month < 12; month++) {
	   	totalMoney += monthlyContribution;
	   	yearlyCapital += monthlyContribution;
	   	totalInvested += monthlyContribution;
	   	totalMoney *= interestPerMonth;
	   	totalMoney -= monthlyFee;
	   	
	   	cpiTotalInvested += monthlyContribution / currentCpi;
	   	currentCpi *= monthlyInflation;
	   }
	   
	   float yearCapitalGains = (totalMoney - startOfYearValue) - yearlyCapital;
	   float payYearlyTax = yearCapitalGains * yearlyTax;
	   totalMoney -= payYearlyTax;
	   
	   /*
	   if (yearlyTax != 0) {
				cout << "Year Capital Gains " << year << ": $" << yearCapitalGains << endl;
				cout << "Year Capital Gains Tax " << year << ": $" << payYearlyTax << endl;
			}
			*/
	}
	
	cout << "Year " << numberOfYears << ": $" << totalMoney << endl;
	
  float totalCapitalGains = (totalMoney - startMoney) - totalInvested;
  float payFinalTax = totalCapitalGains * finalTax;
  totalMoney -= payFinalTax;
	
	// Standard returns
	cout << endl;
	cout << "Final cash: $" << totalMoney << endl;
	cout << "Cash put in: $" << totalInvested << endl;
	
	float profit = totalMoney - totalInvested;
	
	cout << "Profit: $" << profit << endl;
	
	float profitPercentage = profit / totalInvested;
	
	cout << setprecision(2);
	cout << "Percentage Gain: " << profitPercentage * 100 << "%" << endl;
	cout << setprecision(0);
	
	// Inflation adjusted returns
	cout << endl << "Inflation Adjusted, relative CPI is " << setprecision(2) << currentCpi << setprecision(0) << " (" << setprecision(2) << inflation * 100 << setprecision(0) << "% inflation)" << endl;
	
	float cpiMoney = totalMoney / currentCpi;
	
	cout << "Final cash: $" << cpiMoney << endl;
	cout << "Cash put in: $" << cpiTotalInvested << endl;
	
	float cpiProfit = cpiMoney - cpiTotalInvested;
	
	cout << "Profit: $" << cpiProfit << endl;
	
	float cpiProfitPercentage = cpiProfit / cpiTotalInvested;
	
	cout << setprecision(2);
	cout << "Percentage Gain: " << cpiProfitPercentage * 100 << "%" << endl;
	cout << setprecision(0);
	
	cout << endl << endl;
}

int main(int /*argc*/, char** /*argv*/) {
	
	//float startMoney = 0;
	//float monthlyContributionStart = 2000;
	//float monthlyContributionEnd = 2000;
	float startMoney = 50000;
	float monthlyContributionStart = 1000;
	float monthlyContributionEnd = 2220;
	int numberOfYears = 25;
    
	CalculateReturn("Insurance Trust, pay tax at end", 0, monthlyContributionStart, monthlyContributionEnd, 1.035, numberOfYears, 0.0, 0.25, 7);
	
	CalculateReturn("RBC Investment", 0, monthlyContributionStart, monthlyContributionEnd, 1.03, 25, 0.0, 0.0, 0);
	
	CalculateReturn("Canada ETF, pay tax yearly", startMoney, monthlyContributionStart, monthlyContributionEnd, 1.07, numberOfYears, 0.25, 0.0, 0);
	
	CalculateReturn("Canada ETF, pay tax at end", startMoney, monthlyContributionStart, monthlyContributionEnd, 1.07, numberOfYears, 0.0, 0.25, 0);
	
	return 1; 
}
