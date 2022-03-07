import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Collections;
import java.util.Scanner;
/**
 * project1main class is the executable class of this project. It includes the main method.
 * @author Deniz Ünal
 *
 */
public class project1main {
	/**
	 * Reads the input file and provides an output file at the end of the runtime.
	 * @param args input file, output file
	 * @throws FileNotFoundException
	 */
	public static void main(String[] args) throws FileNotFoundException{
		File input = new File(args[0]);
		File output = new File(args[1]);
		
		Scanner in = new Scanner(input);
		PrintStream out = new PrintStream(output);
		
		while(in.hasNext()) {
			String type = in.next();
			if(type.equals("h")) {
				int id = in.nextInt();
				int duration = in.nextInt();
				double rating = in.nextDouble();
				if(duration == 0) {
					House.getHouses().add(new House(id, duration, rating, true));
				} else {
					House.getHouses().add(new House(id,duration, rating, false));
				}
			} else  if(type.equals("s")) {
				int id = in.nextInt();
				String name = in.next();
				int duration = in.nextInt();
				double rating = in.nextDouble();
				if(duration == 0) {
					Student.getUnsettledGraduates().add(new Student(id, name, duration, rating));
				} else {
					Student.getUnsettledStudents().add(new Student(id, name, duration, rating));
				}
			}
			
		}
		
		Collections.sort(House.getHouses());
		Collections.sort(Student.getUnsettledStudents());
		
		while(!Student.getUnsettledStudents().isEmpty()) {
			Term.completeTerm();
		}
		Collections.sort(Student.getUnsettledGraduates());
		
		for(Student graduate: Student.getUnsettledGraduates()) {
			out.println(graduate.name);
		}
		
		in.close();
		out.close();
	}

}
