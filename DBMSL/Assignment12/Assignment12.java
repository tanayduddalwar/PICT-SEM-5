package mongoJava;
import java.util.Scanner;
import org.bson.Document;
import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;

public class Main {
    public static void main(String[] args) {
        try {
            System.out.println("Connecting to MongoDB...");
            MongoClient mongo = new MongoClient("localhost", 27017);
            MongoDatabase db = mongo.getDatabase("mock_prac");
            if (db.getCollection("Employee") == null) {
                db.createCollection("Employee");
            }
            MongoCollection<Document> collection = db.getCollection("Employee");
            Scanner sc = new Scanner(System.in);
            int choice;
            while (true) {
                System.out.println("\nChoose an option:");
                System.out.println("1: Insert");
                System.out.println("2: Update");
                System.out.println("3: Delete");
                System.out.println("4: Display All Documents");
                System.out.println("5: Exit");
                choice = sc.nextInt();
                sc.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        System.out.println("Inserting a new document.");
                        System.out.print("Enter name: ");
                        String name = sc.nextLine();
                        System.out.print("Enter department: ");
                        String dept = sc.nextLine();
                        System.out.print("Enter location: ");
                        String loc = sc.nextLine();
                        System.out.print("Enter salary: ");
                        int salary = sc.nextInt();

                        Document doc = new Document("name", name)
                                        .append("dept", dept)
                                        .append("loc", loc)
                                        .append("salary", salary);
                        collection.insertOne(doc);
                        System.out.println("Document inserted successfully.");
                        break;

                    case 2:
                        System.out.println("Updating a document.");
                        System.out.print("Enter the name of the employee to update: ");
                        String nameToUpdate = sc.nextLine();
                        System.out.print("Enter the new salary: ");
                        int newSalary = sc.nextInt();

                        collection.updateOne(Filters.eq("name", nameToUpdate), Updates.set("salary", newSalary));
                        System.out.println("Document updated successfully.");
                        break;

                    case 3:
                        System.out.println("Deleting a document.");
                        System.out.print("Enter the name of the employee to delete: ");
                        String nameToDelete = sc.nextLine();

                        collection.deleteOne(Filters.eq("name", nameToDelete));
                        System.out.println("Document deleted successfully.");
                        break;

                    case 4:
                        System.out.println("Displaying all documents:");
                        for (Document document : collection.find()) {
                            System.out.println(document.toJson());
                        }
                        break;

                    case 5:
                        System.out.println("Exiting...");
                        mongo.close();
                        sc.close();
                        return;

                    default:
                        System.out.println("Invalid choice. Please try again.");
                        break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
