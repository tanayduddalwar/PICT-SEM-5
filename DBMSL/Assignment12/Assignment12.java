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