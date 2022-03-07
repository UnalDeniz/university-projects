
package question;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;

public class Main {


	public static void main(String args[]) {

		Customer[] customers;
		Operator[] operators;

		int C, O, N;

		File inFile = new File(args[0]);  // args[0] is the input file
		File outFile = new File(args[1]);  // args[1] is the output file
		try {
			PrintStream outstream = new PrintStream(outFile);
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}

		Scanner reader;
		try {
			reader = new Scanner(inFile);
		} catch (FileNotFoundException e) {
			System.out.println("Cannot find input file");
			return;
		}

		C = reader.nextInt();
		O = reader.nextInt();
		N = reader.nextInt();

		customers = new Customer[C];
		operators = new Operator[O];

		//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE
		int nextCustomerID = 0;
		int nextOperatorID = 0;
		
		for(int i = 0;i < N; i++) {
			int type = reader.nextInt();
			if(type == 1) {
				String name = reader.next();
				int age = reader.nextInt();
				Operator operator = operators[reader.nextInt()];
				double limit = reader.nextDouble();
				customers[nextCustomerID] = new Customer(nextCustomerID,name,age,operator,limit);
				nextCustomerID++;
			} 
			else if(type == 2) {
				double tCharge = reader.nextDouble();
				double mCost = reader.nextDouble();
				double nCharge = reader.nextDouble();
				int dRate = reader.nextInt();
				operators[nextOperatorID] = new Operator(nextOperatorID,tCharge,mCost,nCharge,dRate);
				nextOperatorID++;
			} 
			else if(type == 3) {
				Customer caller = customers[reader.nextInt()];
				Customer receiver = customers[reader.nextInt()];
				int time = reader.nextInt();
				caller.talk(time, receiver);
			}
			else if(type == 4) {
				Customer sender = customers[reader.nextInt()];
				Customer receiver = customers[reader.nextInt()];
				int quantity = reader.nextInt();
				sender.message(quantity, receiver);
			}
			else if(type == 5) {
				Customer user = customers[reader.nextInt()];
				double amount = reader.nextDouble();
				user.connection(amount);
			}
			else if(type == 6) {
				Customer payer = customers[reader.nextInt()];
				double amount = reader.nextDouble();
				payer.getBill().pay(amount);
			}
			else if(type  == 7) {
				Customer changer = customers[reader.nextInt()];
				Operator newOperator = operators[reader.nextInt()];
				changer.setOperator(newOperator);
			}
			else if(type == 8) {
				Customer changer = customers[reader.nextInt()];
				double amount = reader.nextDouble();
				changer.getBill().changeTheLimit(amount);
			}
				
		}
		
		reader.close();
		
		PrintStream outstream1;
		try {
		        outstream1 = new PrintStream(outFile);
		}catch(FileNotFoundException e2) {
		        e2.printStackTrace();
		        return;
		}
		
		Customer networkUser = customers[0];
		Customer messageUser = customers[0];
		Customer phoneUser = customers[0];
		
		for(Customer i : customers) {
			if(i.getNetworkUsage() > networkUser.getNetworkUsage()) {
				networkUser = i;
			}
			if(i.getMessageCount() > messageUser.getMessageCount()) {
				messageUser = i;
			}
			if(i.getTalkingAmount() > phoneUser.getTalkingAmount()) {
				phoneUser = i;
			}
		}
		
		for(Operator j : operators) {
			outstream1.println("Operator "+j.ID+" : "+j.getTalkingAmount()+" "+j.getMessageCount()+" "+j.getNetworkUsage());
		}
		
		for(Customer k : customers) {
			outstream1.println("Customer "+k.ID+" : "+k.getBill().getMoneySpent()+" "+k.getBill().getCurrentDebt());
		}
		
		outstream1.println(phoneUser.name + " : " + phoneUser.getTalkingAmount());
		outstream1.println(messageUser.name + " : " + messageUser.getMessageCount());
		outstream1.println(networkUser.name + " : " + networkUser.getNetworkUsage());
		
		outstream1.close();


		//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE
	} 
}

