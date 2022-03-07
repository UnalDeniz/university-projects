import java.util.Collections;
/**
 * Term is the class that computes the graduation and allocation process.
 * @author Deniz Ünal
 *
 */
public class Term {
	/**
	 * The method that computes the graduation and allocation process.
	 */
	public static void completeTerm() {
		
		for(Student student: Student.getUnsettledStudents()) {
			
			for(House house: House.getHouses()) {
				if(!house.isEmpty()) {
					continue;
				}
				
				if(student.rating <= house.rating) {
					house.fillHouse(student);
					Student.getLocatedStudents().add(student);
					break;
				}
			}
			
		}
		Student.getUnsettledStudents().removeAll(Student.getLocatedStudents());
		Collections.sort(Student.getUnsettledStudents());
		
		
		for(Student i:Student.getUnsettledStudents()) {
			i.endTerm();;
			if(i.getDuration() == 0) {
				i.graduate();
			}
		}
		Student.getUnsettledStudents().removeAll(Student.getUnsettledGraduates());
		Collections.sort(Student.getUnsettledStudents());
		
		for(House j: House.getHouses()) {
			if(j.isEmpty()) {
				continue;
			}
			j.endTerm();
			if(j.getDuration() == 0) {
				j.emptyHouse();
			}
		}
	}

}
