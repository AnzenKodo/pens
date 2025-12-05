import java.sql.*;
import java.util.*;
import java.io.*;
import java.nio.file.*;
import java.util.stream.*;

public class DB {
    private static DB instance;
    private Connection connection;
    private String password;

    String url;
    String username;

    private DB(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    static DB init(String url, String username, String password) {
        if (instance == null) {
            instance = new DB(url, username, password);
        }
        return instance;
    }

    void connect() throws SQLException {
        connection = DriverManager.getConnection(url, username, password);
        connection.setAutoCommit(false);
    }

    boolean execStoreProcedure(
        String type, String username, String name, String email, String role,
        boolean isActive, List<Object[]> result
    ) throws SQLException {
        var procType = "";
        if (type == "Add") {
            procType = "A";
        } else if (type == "List") {
            procType = "L";
        } else if (type == "Update") {
            procType = "E";
        } else if (type == "Delete") {
            procType = "D";
        } else {
            throw new SQLException("Given type is not supported: " + type);
        }

        var sql = "{call spMst_User_AV(?, ?, ?, ?, ?, ?)}";
        var stmt = connection.prepareCall(sql);
        stmt.setString(1, procType);
        stmt.setString(2, username);
        stmt.setString(3, name);
        stmt.setString(4, email);
        stmt.setString(5, role);
        stmt.setBoolean(6, isActive);

        var hasResult = stmt.execute();
        connection.commit();
        while (hasResult) {
            try (ResultSet rs = stmt.getResultSet()) {
                ResultSetMetaData metaData = rs.getMetaData();
                int columnCount = metaData.getColumnCount();

                while (rs.next()) {
                    var row = new Object[] {
                        rs.getObject(2), // Name
                        rs.getObject(1), // Username
                        rs.getObject(3), // Email
                        rs.getObject(4), // Role
                        rs.getBoolean(5) == true ? "Active" : "Not Active", // Active
                    };
                    result.add(row);
                }
            }

            hasResult = stmt.getMoreResults();
        }

        return hasResult;
    }

    Object[][] getTable() throws SQLException {
        List<Object[]> result = new ArrayList<>();
        execStoreProcedure("List", "", "", "", "", false, result);
        return result.toArray(Object[][]::new);
    }
    boolean addRow(
        String username, String name, String email, String role, boolean isActive
    ) throws SQLException {
        return execStoreProcedure("Add", username, name, email, role, isActive, null);
    }
    boolean updateRow(
        String username, String name, String email, String role, boolean isActive
    ) throws SQLException {
        return execStoreProcedure("Update", username, name, email, role, isActive, null);
    }
    boolean deleteRow(String username, String email) throws SQLException {
        return execStoreProcedure("Delete", username, "", email, "", false, null);
    }

    static Map<String, String> readEnvFile(String filename) throws IOException {
        return Files.lines(Paths.get(filename))
            .filter(line -> !line.isEmpty()) // Not empty line
            .filter(line -> !line.startsWith("#")) // Not start with '#'
            .map(line -> line.split("=", 2)) // Split after 1st '='
            .filter(arr -> arr.length == 2)
            .collect(Collectors.toMap(
                arr -> arr[0].trim(),
                arr -> arr[1].trim(),
                (existing, replacement) -> replacement
            ));
    }

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        try {
            env = DB.readEnvFile(".env");
        } catch(IOException e) {
            e.printStackTrace();
        }
        DB db = DB.init(env.get("DATABASE_URL"), env.get("USERNAME"), env.get("PASSWORD"));
        try {
            db.connect();
            var result = db.getTable();
            System.out.println(result[0][0]);
            System.out.println("Connected to DB");
        } catch(SQLException e) {
            e.printStackTrace();
        }
    }
}
