package assign8;

import java.sql.*;
import java.util.*;

public class java_connectivity {
    public static void main(String[] args) {
        try {
            // Load the MySQL driver
            Class.forName("com.mysql.jdbc.Driver");
            System.out.println("Driver loaded successfully");

            // Establish the database connection
            Connection cn = DriverManager.getConnection("jdbc:mysql://10.10.13.97:3306/te31123_db", "te31123", "te31123");
            Statement st = cn.createStatement();

            // User input for choice
            System.out.println("Enter the choice:");
            System.out.println("1. Insert");
            System.out.println("2. Delete");
            System.out.println("3. Update");
            Scanner scanner = new Scanner(System.in);
            int choice = scanner.nextInt();

            switch (choice) {
            case 1:
                // Insert operation
                System.out.println("Enter the Location:");
                String loc = scanner.next();
                System.out.println("Enter the name of dept:");
                String name = scanner.next();
                System.out.println("Enter the ID of dept:");
                int id = scanner.nextInt();

                // Insert query
                String insertQuery = "INSERT INTO dept (dept_ID, dept_name, location) VALUES (?, ?, ?)";
                PreparedStatement pstmt = cn.prepareStatement(insertQuery);
                pstmt.setInt(1, id); // dept_ID
                pstmt.setString(2, name); // dept_name
                pstmt.setString(3, loc); // location
                pstmt.executeUpdate();
                System.out.println("Insert successful");
                break;

                case 2:
                System.out.println("Enter the dept ID to delete:");
                     int deptId = scanner.nextInt();
                     String deleteQuery = "DELETE FROM dept WHERE dept_ID=?";
                     pstmt = cn.prepareStatement(deleteQuery);
                     pstmt.setInt(1, deptId);
                     pstmt.executeUpdate();
                     System.out.println("Delete successful");
                     break;


                case 3:
                System.out.println("Enter the dept name to update location");
                String dep=scanner.next();
                System.out.println("Enter the location to update:");
                String loca=scanner.next();
                String updatequery="Update  dept set location=? where dept_name=? ";
                pstmt = cn.prepareStatement(updatequery);
                pstmt.setString(1,loca);
                pstmt.setString(2, dep);
                //pstmt.updateString()
                pstmt.executeUpdate();
                System.out.println("Update successful");
               
                    // Placeholder for update operation
                    //System.out.println("Update operation not implemented yet.");
                    break;

                default:
                    System.out.println("Invalid choice");
                    break;
            }

            // Fetch and display employees
            ResultSet rs = st.executeQuery("SELECT dept_ID, dept_name,location FROM dept");
            while (rs.next()) {
                System.out.println(rs.getInt(1) + " " + rs.getString(2)+" "+rs.getString(3));
            }

            // Close resources
            rs.close();
            st.close();
            cn.close();
            scanner.close();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
