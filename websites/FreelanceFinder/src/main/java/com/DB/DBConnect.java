package com.DB;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class DBConnect {

    private static Connection connection;

    public static Connection getConnection() {
        try {
            if(connection == null) {
                // SQLite JDBC driver class
                Class.forName("org.sqlite.JDBC");

                // SQLite database path
                String dbPath = "jdbc:sqlite:job_portal.db";

                // Create connection
                connection = DriverManager.getConnection(dbPath);

                // Initialize the database
                initializeDatabase();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return connection;
    }

    private static void initializeDatabase() {
        try {
            // Read the SQL script
            BufferedReader reader = new BufferedReader(new InputStreamReader(
                DBConnect.class.getResourceAsStream("/init_db.sql")));

            StringBuilder script = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                script.append(line).append("\n");
            }

            // Execute the SQL script
            Statement stmt = connection.createStatement();
            stmt.executeUpdate(script.toString());
            stmt.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
