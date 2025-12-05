import java.util.*;
import java.io.*;
import javax.swing.*;
import javax.swing.table.*;
import java.sql.*;

public class Main {
    static DB db;

    private static int findUsername(String name, DefaultTableModel dataModel) {
        int output = -1;
        int rows = dataModel.getRowCount();
        for (int row = 0; row < rows; row++) {
            Object cellValue = dataModel.getValueAt(row, 1);
            if (cellValue != null && cellValue.equals(name)) {
                output = row;
                break;
            }
        }
        return output;
    }
    private static int findEmail(String email, DefaultTableModel dataModel) {
        int output = -1;
        int rows = dataModel.getRowCount();
        for (int row = 0; row < rows; row++) {
            Object cellValue = dataModel.getValueAt(row, 2);
            if (cellValue != null && cellValue.equals(email)) {
                output = row;
                break;
            }
        }
        return output;
    }

    private static LinkedHashMap<String, String> extractFormValues(
        LinkedHashMap<String, JComponent> entries
    ) {
        var values = new LinkedHashMap<String, String>();
        values.put("Name", ((JTextField)entries.get("Name")).getText().trim());
        values.put("Username", ((JTextField)entries.get("Username")).getText());
        values.put("Email", ((JTextField)entries.get("Email")).getText());
        values.put("Role", ((JComboBox<?>)entries.get("Role")).getSelectedItem().toString());
        values.put("Status", ((JCheckBox)entries.get("Status")).isSelected() ? "Active" : "Not Active");
        return values;
    }

    private static boolean validateFormValues(
        LinkedHashMap<String, String> values, DefaultTableModel dataModel
    ) {
        var errorMessages = new StringBuilder();
        var valied = true;
        if (values.get("Name").isEmpty()) {
            errorMessages.append("- Name can't be empty!\n");
            valied = false;
        }
        // Username
        if (values.get("Username").isEmpty()) {
            errorMessages.append("- Username can't be empty!\n");
            valied = false;
        }
        var usernameAllowedChars = "[a-zA-Z0-9_]+";
        if (!values.get("Username").matches(usernameAllowedChars)) {
            errorMessages.append(
                "- Username can only have following charactors:"
                + usernameAllowedChars.substring(0, usernameAllowedChars.length() - 1) + "\n");
            valied = false;
        }
        // Email
        if (values.get("Email").isEmpty()) {
            errorMessages.append("- Email can't be empty!\n");
            valied = false;
        }
        if (!values.get("Email").matches("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$")) {
            errorMessages.append("- Email should follow following format: abc@example.com\n");
            valied = false;
        }
        if (values.get("Role") == "Select Role") {
            errorMessages.append("- Please, select role for User!\n");
            valied = false;
        }
        if (!valied) {
            JOptionPane.showMessageDialog(
                null, errorMessages.toString(), "Error", JOptionPane.WARNING_MESSAGE
            );
        }
        return valied;
    }

    public static void saveToCsv(DefaultTableModel model, String path) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(path))) {
            // Head
            for (int col = 0; col < model.getColumnCount(); col++) {
                writer.write("\"" + model.getColumnName(col) + "\"");
                if (col < model.getColumnCount() - 1) {
                    writer.write(",");
                }
            }
            writer.newLine();

            // Rows
            for (int row = 0; row < model.getRowCount(); row++) {
                for (int col = 0; col < model.getColumnCount(); col++) {
                    Object value = model.getValueAt(row, col);
                    writer.write("\"" + (value == null ? "" : value.toString()) + "\"");
                    if (col < model.getColumnCount() - 1) {
                        writer.write(",");
                    }
                }
                writer.newLine();
            }
        }
    }
    public static void clearFields(LinkedHashMap<String,JComponent> fields) {
        ((JTextField)fields.get("Name")).setText("");
        ((JTextField)fields.get("Username")).setText("");
        ((JTextField)fields.get("Email")).setText("");
        ((JComboBox)fields.get("Role")).setSelectedIndex(0);
        ((JCheckBox)fields.get("Status")).setSelected(false);
    }

    public static void start() {
        var gui = new GUI("User Management System", 500, 500);

        var fields = new LinkedHashMap<String, JComponent>();
        fields.put("Name", gui.new TextField(100));
        fields.put("Username", gui.new TextField(100));
        fields.put("Email", gui.new TextField(100));
        String[] roles = { "Select Role", "Admin", "User", "Guest" };
        fields.put("Role", new JComboBox<>(roles));
        fields.put("Status", new JCheckBox("Active"));
        gui.createFormFields(fields);

        var fieldsKeys = Arrays.stream(fields.keySet().toArray())
            .map(obj -> (String)obj).toArray(String[]::new);

        try {
            var data = db.getTable();
            gui.createTable(fieldsKeys, data);
        } catch(SQLException e) {
            JOptionPane.showMessageDialog(
                null, "Error: Can't get database table value. " + e.getClass().getName() + " " + e.getMessage(),
                "Database Error",
                JOptionPane.ERROR_MESSAGE
            );
            System.exit(1);
        }

        var dataModel = gui.getTableModel();
        gui.setTableSelectionListener(() -> {
            var formFieldMap = extractFormValues(fields);
            var overrideData = true;
            if (
                !formFieldMap.get("Name").isEmpty() ||
                !formFieldMap.get("Username").isEmpty() ||
                !formFieldMap.get("Email").isEmpty()
            ) {
                 overrideData = JOptionPane.showConfirmDialog(
                    null, "Are you sure you want to override form fields!",
                    "Override Comfirmation", JOptionPane.YES_NO_OPTION
                ) == 0 ? true : false;
            }
            if (overrideData) {
                var selectedRow = gui.getTableSelectedRow();
                ((JTextField)fields.get("Name")).setText(dataModel.getValueAt(selectedRow, 0).toString());
                ((JTextField)fields.get("Username")).setText(dataModel.getValueAt(selectedRow, 1).toString());
                ((JTextField)fields.get("Email")).setText(dataModel.getValueAt(selectedRow, 2).toString());
                ((JComboBox)fields.get("Role")).setSelectedIndex(
                    Arrays.asList(roles).indexOf(dataModel.getValueAt(selectedRow, 3))
                );
                ((JCheckBox)fields.get("Status")).setSelected(
                    dataModel.getValueAt(selectedRow, 4) == "Active" ? true : false
                );
            }
        });
        gui.createFormButton("Add", (e) -> {
            var formFieldMap = extractFormValues(fields);
            if (validateFormValues(formFieldMap, dataModel)) {
                boolean isValid = true;
                var errorMessages = new StringBuilder();

                if (findUsername(formFieldMap.get("Username"), dataModel) > -1) {
                    errorMessages.append("- Username already exists: \n" + formFieldMap.get("Username"));
                    isValid = false;
                }
                if (findEmail(formFieldMap.get("Email"), dataModel) > -1) {
                    errorMessages.append("- Email already exists: " + formFieldMap.get("Email"));
                    isValid = false;
                }
                if (isValid) {
                    try {
                        db.addRow(
                            formFieldMap.get("Username"),
                            formFieldMap.get("Name"),
                            formFieldMap.get("Email"),
                            formFieldMap.get("Role"),
                            formFieldMap.get("Status") == "Active" ? true : false
                        );
                        dataModel.addRow(new String[] {
                            formFieldMap.get("Username"),
                            formFieldMap.get("Name"),
                            formFieldMap.get("Email"),
                            formFieldMap.get("Role"),
                            formFieldMap.get("Status")
                        });
                        clearFields(fields);
                    } catch(SQLException er) {
                        JOptionPane.showMessageDialog(
                            null,
                            "Error: Can't add update to Databse. " +
                                er.getClass().getName() + " " + er.getMessage(),
                            "Database Error",
                            JOptionPane.ERROR_MESSAGE
                        );
                    }
                } else {
                    JOptionPane.showMessageDialog(
                        null, errorMessages.toString(), "Error", JOptionPane.WARNING_MESSAGE
                    );
                }
            };
        });
        gui.createFormButton("Update", (e) -> {
            var formFieldMap = extractFormValues(fields);
            if (validateFormValues(formFieldMap, dataModel)) {
                int rowIndex = findUsername(formFieldMap.get("Username"), dataModel);
                if (rowIndex < 0) {
                    JOptionPane.showMessageDialog(
                        null,
                        "Can't find entered username: " + formFieldMap.get("Username"),
                        "Error",
                        JOptionPane.WARNING_MESSAGE
                    );
                } else {
                    try {
                        db.updateRow(
                            formFieldMap.get("Username"),
                            formFieldMap.get("Name"),
                            formFieldMap.get("Email"),
                            formFieldMap.get("Role"),
                            formFieldMap.get("Status") == "Active" ? true : false
                        );
                        var values = formFieldMap.values().toArray();
                        for (int col = 0; col < values.length; col++) {
                            dataModel.setValueAt(values[col], rowIndex, col);
                        }
                    } catch(SQLException er) {
                        JOptionPane.showMessageDialog(
                            null,
                            "Error: Can't add update to Databse. " +
                                er.getClass().getName() + " " + er.getMessage(),
                            "Database Error",
                            JOptionPane.ERROR_MESSAGE
                        );
                    }
                }
            }
        });
        gui.createFormButton("Delete", (e) -> {
            var selectedRow = gui.getTableSelectedRow();
            if (selectedRow > -1) {
                var deleteComfirmation = JOptionPane.showConfirmDialog(
                    null, "Do want to delete this row!",
                    "Deletion Comfirmation", JOptionPane.YES_NO_OPTION
                );
                if (deleteComfirmation == 0) {
                    try {
                        var username = gui.getTableColValue(selectedRow, 1);
                        var email = gui.getTableColValue(selectedRow, 2);
                        db.deleteRow(username, email);
                        dataModel.removeRow(selectedRow);
                    } catch(SQLException er) {
                        JOptionPane.showMessageDialog(
                            null,
                            "Error: Can't delete row in Databse. " +
                                er.getClass().getName() + " " + er.getMessage(),
                            "Database Error",
                            JOptionPane.ERROR_MESSAGE
                        );
                    }
                }
            } else {
                JOptionPane.showMessageDialog(
                    null, "Please, select a row to delete.",
                    "Error", JOptionPane.WARNING_MESSAGE
                );
            }
        });
        gui.createFormButton("Clear", (e) -> {
            clearFields(fields);
        });
        gui.createFormButton("Save", (a) -> {
            try {
                saveToCsv(dataModel, "./build/data.csv");
            } catch (IOException error) {
                error.printStackTrace();
            }
        });
    }

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        try {
            env = DB.readEnvFile(".env");
        } catch(IOException e) {
            JOptionPane.showMessageDialog(
                null, "Error: " + e.getClass().getName() + " " + e.getMessage(),
                ".env File Error",
                JOptionPane.ERROR_MESSAGE
            );
            System.exit(1);
        }

        db = DB.init(env.get("DATABASE_URL"), env.get("USERNAME"), env.get("PASSWORD"));
        try {
            db.connect();
        } catch(SQLException e) {
            JOptionPane.showMessageDialog(
                null, "Error: Can't connect to Databse. " + e.getClass().getName() + " " + e.getMessage(),
                "Database Error",
                JOptionPane.ERROR_MESSAGE
            );
            System.exit(1);
        }

        SwingUtilities.invokeLater(Main::start);
    }
}
