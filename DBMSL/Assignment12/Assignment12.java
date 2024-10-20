package v3;

import java.util.*;

import com.mongodb.MongoClient;
import com.mongodb.client.*;
import com.mongodb.MongoCredential;
import com.mongodb.ServerAddress;
import org.bson.Document;

public class Mongo{
	public static void main(String[] args){
		MongoCredential client=new MongoClient("127.0.0.1",27017);
	// 	    MongoCredential credentials = MongoCredential.createCredential("te31123","te31123_db", "te31123".toCharArray());
    // MongoClient client = new MongoClient(new ServerAddress("10.10.12.248",27017), Arrays.asList(credentials));

		System.out.println("Connected to DB");
		MongoDatabase db=client.getDatabase("31123_db");
		MongoCollection<Document>collection=db.getCollection("Employee");
		Scanner sc=new Scanner(System.in);
		while(true){
			System.out.println("Menu:");
            System.out.println("1. Create");
            System.out.println("2. Read");
            System.out.println("3. Update");
            System.out.println("4. Delete");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
			int choice=sc.nextInt();
			switch(choice){
				case 1:
					createdocument(collection,sc);
				case 2:
					readDocuments(collection);
				case 3:
                    updateDocument(collection, sc);
                    break;

                case 4:
                    deleteDocument(collection, sc);
                    break;

			}
			System.out.println("Continue? (y/n): ");
            String ans = sc.next();
            if (ans.equals("N") || ans.equals("n"))
                break;
		}
		sc.close();
		client.close();
	}
	System.out.println("Continue? (y/n): ");
            String ans = sc.next();
            if (ans.equals("N") || ans.equals("n"))
                break;
}
 public static void createDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter a key: ");
        String key = sc.next();
        System.out.println("Enter its value: ");
        String value = sc.next();
        Document newdoc = new Document(key, value);
        collection.insertOne(newdoc);
        System.out.println("Document inserted successfully");

    }

    public static void readDocuments(MongoCollection<Document> collection) {
        for (Document doc : collection.find()) {
            System.out.println(doc.toJson());
        }
    }

    public static void updateDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter document identifier key: ");
        String key = sc.next();
        System.out.println("Enter corresponding value");
        String value = sc.next();
        Document filter = new Document(key, value);
        System.out.println("Enter new value");
        String uValue = sc.next();
        Document uDoc = new Document(key, uValue);
        collection.updateOne(filter, uDoc);
        System.out.println("Document updated successfully");
    }

    public static void deleteDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter document identifier key: ");
        String key = sc.next();
        System.out.println("Enter corresponding value");
        String value = sc.next();
        Document filter = new Document(key, value);
        collection.deleteOne(filter);
        System.out.println("Document deleted successfully");

    }