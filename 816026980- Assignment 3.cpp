#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

// useful constants

#define QUIT 8	
#define PERCENT 100	   

struct stockData{
	string stockName;
	float open;
	float high;
	float low;
	float close;
	int volume;
};

struct DateData{
	int dateID;
	int day;
	int month;
	int year;
};

struct symbolData{
	int symbolID;
	string symbolStr;
};



int readSymbolFile(int numSymbols, symbolData symbol[]){
	
	//returns num rows
	
	ifstream symbolFile;

	int c=0;
	int symbolTemp;
	
	
	symbolFile.open("symbol.txt");
	
	
	if ((!symbolFile.is_open())) {
		cout << "\nERROR: Symbol file cannot be found...Try again\n";
	}
	else 	
		cout<<"Symbol file was Read Successfully... "<<endl<<endl; 
	
	symbolFile>>symbolTemp;
	
	while ( symbolTemp != -1){
		symbol[numSymbols].symbolID= symbolTemp;
		symbolFile>>symbol[numSymbols].symbolStr;
		
		numSymbols++;
		
		symbolFile>>symbolTemp;
	}
	
	return numSymbols;
}


void printSymbolFile(int numSymbols, symbolData symbol[]){
	
	//to test data
	
	int c;
	cout<<"Printing Symbol File..."<<endl<<endl;
	
	for (c=0; c< numSymbols; c++ ){
		cout<<"ID: "<<symbol[c].symbolID<<"\t Symbol: "<<symbol[c].symbolStr<< endl;
	}
	
}


int readDateFile(DateData date [], int numDays){
	
	//returns num Columns
	
	ifstream dateFile;

	int c=0;
	int dateTemp;

	dateFile.open("date.txt");
	
	
	if ((!dateFile.is_open())) {
		cout << "\nERROR: Date file cannot be found...Try again\n";
	}
	else 	
		cout<<"Date file was Read Successfully... "<<endl<<endl; 
	
	
	dateFile>>dateTemp;
	while ( dateTemp != -1 ){
		date[numDays].dateID=dateTemp;	
		dateFile>>date[numDays].day;
		dateFile>>date[numDays].month;
		dateFile>>date[numDays].year;
		
		numDays++;
		
		dateFile>>dateTemp;
	}
	
	return numDays;
}


void printDateFile( DateData date[], int numDays){
	
	//to test data
	int c;
	
	cout<<"\n\nPrinting Date File..."<<endl<<endl;
	
	for (c=0; c< numDays; c++ ){
		cout<<"ID: "<<date[c].dateID<<"\t day: "<<date[c].day<<"\t month: "<<date[c].month<<"\t year: "<<date[c].year<< endl;
	}
	
}


void readStockFile(stockData stock[100][30], int numSymbols, int numDays){
	
	ifstream stockFile; 

	int c=0;
	string stockTemp;
	
	stockFile.open("stock.txt");
	
	if ((!stockFile.is_open())) {
		cout << "\nERROR: Stock file cannot be found...Try again\n";
	}
	else 	
		cout<<"Stock file was Read Successfully... "<<endl<<endl; 
	
	
	int row=0;
	int col=0;
	
	
	stockFile>>stockTemp;
	
	while( stockTemp != "END"){
	
		for (int row =0; row<numSymbols; row++){
			for (int col=0; col<numDays; col++){
				stock[row][col].stockName=stockTemp;
				stockFile>>stock[row][col].open;
				stockFile>>stock[row][col].high;
				stockFile>>stock[row][col].low;
				stockFile>>stock[row][col].close;
				stockFile>>stock[row][col].volume;
			
			}
			stockFile>>stockTemp;
	
		}
	
	}
	
}


void printStockFile( stockData stock[100][30], int numSymbols, int numDays ){

	//to test data
	
	cout<<"\n\nPrinting Stock File..."<<endl<<endl;
	
	for (int row =0; row<numSymbols; row++){
			for (int col=0; col<numDays; col++){
				
				cout<<"\t"<<stock[row][col].stockName;
				cout<<"\t"<<stock[row][col].open;
				cout<<"\t"<<stock[row][col].high;
				cout<<"\t"<<stock[row][col].low;
				cout<<"\t"<<stock[row][col].close;
				cout<<"\t"<<stock[row][col].volume;
				cout<<endl<<endl;
				
			}
	}
}


int searchSymbol(stockData stock[100][30], int numSymbols, int numDays, DateData date [], symbolData symbol[], string findSymbol){
	
	//gets a row
	//checks for valid symbol
	
	int i;

    for (i=0;i<numSymbols;i++){
    	
        if (symbol[i].symbolStr == findSymbol){
                return i;
            }
    }
	return -1;
	
}


int searchDate(stockData stock[100][30], int numSymbols, int numDays, DateData date [], symbolData symbol[], int dayInput, int monthInput, int yearInput){
	
	//gets a column
	//checks for valid date
	
	int i; 

    for (i=0;i<numDays;i++){
    	
        if ((date[i].day == dayInput)&&(date[i].month== monthInput)&& (date[i].year==yearInput)){ 
                return i;
            }
    }
    
	return -1;
	
}


void initialize2D (char star[][30], int numSymbols, int numDays){
	
	for (int row =0; row<numSymbols; row++)
			for (int col=0; col<numDays; col++)
				star[row][col] = ' ';

}


void initialize1D (int closing[],int numDays){
	
	for (int i= 0; i< numDays; i++){
		closing[i]=0;
	}
}


void option1 (stockData stock[][30], int numSymbols, int numDays, DateData date [], symbolData symbol[], string find){
	
	//Find the highest closing price of a given stock and the date on which it occurred
	
	int symLoc = searchSymbol(stock,numSymbols,numDays,date,symbol,find);
	
	//if it is a valid symbol...
	if (symLoc != -1){
		float highestClose=0.0;
		int highestDay=0;
		int highestMonth=0;
		int highestYear=0;
		int col=0;
		
		highestClose= stock[symLoc][col].close; // set highest to the first value
		
		for (col=0; col<numDays; col++){
			
			if(stock[symLoc][col].close > highestClose){
			
				highestClose = stock[symLoc][col].close;
				highestDay= date[col].day;
				highestMonth= date[col].month;
				highestYear= date[col].year;
			}
		}
		cout<< "\nHighest closing price of "<<find<< " is: "<<highestClose<<endl; 
		cout<< "It occured on: "<< highestDay<<"/"<<highestMonth<<"/"<<highestYear<<"."<<endl;

	}
	else
		cout<<"\nThis symbol was not found. Please try again."<<endl;
	
}


void option2 (stockData stock[][30], int numSymbols, int numDays, DateData date [], symbolData symbol[], string find){
	
	//Find the total volume traded of a given stock
	
	int symLoc = searchSymbol(stock,numSymbols,numDays,date,symbol,find);
	int volumeSum=0;
	
	if (symLoc != -1){
		
		for (int col=0; col<numDays; col++){
			volumeSum += stock[symLoc][col]. volume;
		}
		
		cout<<"\nThe total volume traded of "<< find <<" is "<<volumeSum<<endl;
		
	}
	else
		cout<<"\nThis symbol was not found. Please try again."<<endl;
}


void option3 (stockData stock[][30], int numSymbols, int numDays, DateData date [], symbolData symbol[], string find){
	
	//Find the date of the biggest difference between high and low prices of a given stock
	
	int symLoc = searchSymbol(stock,numSymbols,numDays,date,symbol,find);
	
	if (symLoc != -1){
		
		float diff=0.0;
		float highestDiff=0.0;
		float high=0.0;
		float low=0.0;
		float highPrice=0.0;
		float lowPrice=0.0;
		int highestDay=0;
		int highestMonth=0;
		int highestYear=0;
		
		int col;
		
		for (col=0; col<numDays; col++){
			
			high= stock[symLoc][col].high;
			low= stock[symLoc][col].low;
			diff=high-low;
			
			if(diff > highestDiff){
				highPrice = high;
				lowPrice=low;
				highestDiff = diff;
				highestDay= date[col].day;
				highestMonth= date[col].month;
				highestYear= date[col].year;
			}
		}
		cout<< "\nThe biggest difference of "<<fixed<< setprecision(2) << highestDiff<<" between high and low was on "<< highestDay <<"/"<<highestMonth<<"/"<<highestYear<<"."<<endl;
		cout<< "The high price was: "<<highPrice<<endl;
		cout<< "The Low price was: "<<lowPrice<<endl;
	}
	else
		cout<<"\nThis symbol was not found. Please try again."<<endl;
}
	
	
void option4 (stockData stock[][30], int numSymbols, int numDays, DateData date [], symbolData symbol[], int dayInput, int monthInput,  int yearInput){
	
	//Find the stock with the biggest difference between high and low prices on a given date
	
	int dateLoc = searchDate(stock, numSymbols, numDays,date ,symbol, dayInput, monthInput,  yearInput );
	
	if (dateLoc != -1){
		float diff=0.0;
		float highestDiff=0.0;
		float high=0.0;
		float low=0.0;
		float highPrice=0.0;
		float lowPrice=0.0;
		string highestStock;
	
		int row;
		
		for (row=0; row<numSymbols; row++){
			
			high= stock[row][dateLoc].high;
			low= stock[row][dateLoc].low;
			diff=high-low;
			
			if(diff > highestDiff){
				highestDiff = diff;
				highPrice = high;
				lowPrice=low;
				highestStock= symbol[row].symbolStr;
			}
		}
		cout<< "\nThe biggest difference of "<<fixed<< setprecision(2) << highestDiff<<" between high and low on "<< dayInput <<"/"<<monthInput<<"/"<<yearInput<<" was "<<highestStock<<endl;
		cout<< "The high price was: "<<highPrice<<endl;
		cout<< "The Low price was: "<<lowPrice<<endl;
	
	}
	else
		cout<< "\nThis date was not found. Please try again."<<endl;
}


void option5 ( stockData stock[][30], int numSymbols, int numDays, DateData date [], symbolData symbol[] ){
	
	//Find the biggest changing stock price between a previous day's close and next day's open
	
	float nextOpen=0.0;
	float prevClose = 0.0;
	float diff = 0.0;
	float highestDiff = 0.0;
	float open=0.0;
	float close=0.0;
	
	int prevDay=0;
	int prevMonth=0;
	int prevYear=0;
	
	int nextDay=0;
	int nextMonth=0;
	int nextYear=0;
	
	string highestStock;
	
	for (int row =0; row<numSymbols; row++){
			for (int col=0; col<numDays; col++){
				
				prevClose=stock[row][col].close;
				nextOpen= stock[row][col+1].open;
				diff= nextOpen - prevClose ; 
				
				if((diff > highestDiff) && (diff != prevClose)){
					
					highestDiff = diff;
					open = prevClose;
					close =nextOpen;
					highestStock= symbol[row].symbolStr;
					
					prevDay= date[col].day;
					prevMonth= date[col].month;
					prevYear= date[col].year;
					
					nextDay= date[col+1].day;
					nextMonth= date[col+1].month;
					nextYear= date[col+1].year;
				}
			}
		}
		cout<< "\nThe biggest difference of "<<fixed<< setprecision(2) << highestDiff<<" between Previous Closing Price and Next Day Opening Price was for "<<highestStock<<endl;
		cout<< "The Previous Closing Price was: "<<open<<endl;
		cout<< "The Next Day Opening Price was: "<<close<<endl;
		cout<< "The Previous Closing Price was on " << prevDay << "/" << prevMonth << "/"<<prevYear << " and Next Day Opening Price was on "<< nextDay << "/" << nextMonth << "/"<<nextYear <<endl;
	
}


void option6( stockData stock[][30], int numSymbols, int numDays, DateData date [], symbolData symbol[] ){
	
	//Find the percentage increase/decrease of each stock based on first day / last day prices
	
	float firstClose=0.0;
	float lastClose = 0.0;
	float change = 0.0;
	float percentChange=0.0;
	
	cout<< "\n\tStock Symbol \t Increase/Decrease "<<endl;
	
	for (int row =0; row<numSymbols; row++){
			for (int col=0; col<numDays; col++){
				
				firstClose=stock[row][col].close;
				lastClose= stock[row][numDays-1].close;
				change = lastClose - firstClose ; 
				
				percentChange = (change/firstClose) * PERCENT; 
				col = numDays; 
				
				}
			
			cout<< "\t "<<symbol[row].symbolStr << "\t\t\t"<<fixed<< setprecision(1) << percentChange <<endl;
		}
	
}


void printArr(int closing[], int numDays){
	
	for (int i =0; i <numDays;i++){
		cout<<closing[i]<<"\t";
	}
}


void print2DArr(char star[][30], int numSymbols, int numDays){
	
	for (int row =0; row<numSymbols; row++)
			for (int col=0; col<numDays; col++)
				cout<< star[row][col];
	
}


void option7 (stockData stock[][30], int numSymbols, int numDays, DateData date [], symbolData symbol[], char star[][30], int closing[], string find){
	
	//Plot a graph showing the price of a given stock on each day
	
	int symLoc = searchSymbol(stock,numSymbols,numDays,date,symbol,find);
	
	initialize2D(star, numSymbols, numDays);
	initialize1D(closing, numDays);
	
	if (symLoc != -1){
		
		float highestClose=0.0;
		int highestDay=0;
		int closingPrice;
	
		int col=0;
		
		highestClose= stock[symLoc][col].close;
		
		int firstDate= date[col].day;
		int firstMonth= date[col].month;
		int firstYear= date[col].year;
		
		int lastDate= date[numDays-1].day;
		int lastMonth= date[numDays-1].month;
		int lastYear= date[numDays-1].year;
		
		
		for (col=0; col<numDays; col++){
			
			closingPrice = (int) round (stock[symLoc][col].close);
			
			closing[col]= closingPrice; 
			
			if(stock[symLoc][col].close > highestClose){
			
				highestClose = stock[symLoc][col].close;
				highestDay= date[col].day;
				
			}
		}
		
		int highPrice = ((int) round (highestClose))+ 1;
		
//		printArr(closing,numDays);
//		print2DArr(star, numSymbols,numDays);
		
		cout<<"\nGraph of Closing Price for "<<find<<" from "<< firstDate << "/" << firstMonth << "/"<<firstYear <<" to "<< lastDate << "/" << lastMonth << "/"<<lastYear <<endl;

		cout<<"\n\tPrice \t\t Data"<<endl<<endl;
		
		for (int row =highPrice; row >= 0; row--){
			cout<<"\t"<<row;
			
			for (int col=0; col<numDays; col++){
				
				if (closing[col] == row){
					star[row][col]='*';
					cout<<star[row][col];
				}
				else 
					cout<<" ";
				
			}
			cout<<endl;
		}
		
	}
	else 
		cout<<"\nThis symbol was not found. Please try again."<<endl;
	
}


int menu () {

	int option;
	bool validOption;
	
	validOption = false;
	
	while (!validOption) {
		cout << endl;
		cout << "\n\n\t\t\t\tCOMP 1602 ASSIGNMENT 3: STOCK EVALUATION " << endl;
		cout << "\t\t\t\t----------------------------------------" << endl;
		cout << endl;
		cout << "\t  Enter 1:  To find the highest closing price of any stock and the date on which it occurred." << endl;
		cout << "\t  Enter 2:  To find the total volume traded of a given stock." << endl;
		cout << "\t  Enter 3:  To find the date of the biggest difference between high and low prices of a given stock" << endl;
		cout << "\t  Enter 4:  To find the stock with the biggest difference between high and low prices on a given date" << endl;
		cout << "\t  Enter 5:  To find the biggest changing stock price between a previous day's close and next day's open" << endl;
		cout << "\t  Enter 6:  To find the percentage increase/decrease of each stock based on first day / last day prices" << endl;
		cout << "\t  Enter 7:  To plot a graph showing the price of a given stock on each day" << endl;
		cout << "\n\t  Please choose an option or " << QUIT << " to quit: ";
		cin  >> option;
	
		if (option >= 1 && option <= QUIT)	// QUIT is a constant; its use is optional.
			validOption = true;
		else{
			cout<<"\nSorry, option 1 to " << QUIT <<" must be entered. Please try again."<<endl;
			//system("cls");	
		}
			
	}								
	
	return option;
}


int main (){
	
	stockData stock[100][30];
	DateData date [30];
	symbolData symbol[100];
	
	int numSymbols=0; //m number of stock symbols
	int numDays=0; //n number of days
	int count=0;
	
	
	numSymbols= readSymbolFile(numSymbols, symbol);
	numDays= readDateFile(date, numDays);
	readStockFile(stock, numSymbols, numDays);
	
//	printSymbolFile(numSymbols,symbol);
//	printDateFile(date, numDays);
//	printStockFile( stock, numSymbols, numDays );

	char star[100][30];
	int closing [ numDays ];
	
	int choice= menu();
	
	string symbolInput;
	int dayInput, monthInput, yearInput;
	
	while (choice != QUIT){
		
		if (choice == 1){
			
			cout<<"\nPlease enter the stock symbol: ";
			cin>> symbolInput;
			option1(stock, numSymbols, numDays, date, symbol, symbolInput);
			
		}
		else
			if (choice == 2){
				
				cout<<"\nPlease enter the stock symbol: ";
				cin>> symbolInput;
				option2(stock, numSymbols, numDays, date, symbol, symbolInput);
			
			}
			else
				if (choice == 3){
					
					cout<<"\nPlease enter the stock symbol: ";
					cin>> symbolInput;
					option3(stock, numSymbols, numDays, date, symbol, symbolInput);
		
				}
				else
					if (choice == 4){
						
						cout<<"\nPlease enter the date you'd like to check: ";
						cin>> dayInput >>monthInput>>yearInput;
						option4(stock, numSymbols, numDays, date, symbol, dayInput ,monthInput, yearInput);
						
					}
					else
						if (choice == 5){
							
							option5 (stock, numSymbols, numDays,date, symbol);
							
						}
						else
							if (choice == 6){
								
								option6(stock, numSymbols, numDays,date, symbol);
	
							}
							else
								if (choice == 7){
									
									cout<<"\nPlease enter the stock symbol to create a graphical representation: ";
									cin>> symbolInput;
									option7(stock, numSymbols, numDays, date, symbol, star, closing, symbolInput);
		
								}
										
		choice=menu();
	}

	
	return 0;

}

