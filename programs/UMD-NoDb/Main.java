import java.util.*;
import java.io.*;
import javax.swing.*;
import javax.swing.table.*;

public class Main {
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

    private static LinkedHashMap<String, String> extractFormValues(LinkedHashMap<String, JComponent> entries) {
        var values = new LinkedHashMap<String, String>();
        values.put("Name", ((JTextField)entries.get("Name")).getText().trim());
        values.put("Username", ((JTextField)entries.get("Username")).getText());
        values.put("Email", ((JTextField)entries.get("Email")).getText());
        values.put("Role", ((JComboBox<?>)entries.get("Role")).getSelectedItem().toString());
        values.put("Status", ((JCheckBox)entries.get("Status")).isSelected() ? "Active" : "Not Active");
        return values;
    }

    private static boolean validateFormValues(LinkedHashMap<String, String> values, DefaultTableModel dataModel) {
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

    public static void start() {
        var gui = new GUI("User Management System", 500, 500);

        var fields = new LinkedHashMap<String, JComponent>();
        fields.put("Name", new JTextField());
        fields.put("Username", new JTextField());
        fields.put("Email", new JTextField());
        String[] roles = { "Select Role", "Admin", "User", "Guest" };
        fields.put("Role", new JComboBox<>(roles));
        fields.put("Status", new JCheckBox("Active"));
        gui.createFormFields(fields);

        Object data[][] = {
            { "Frodo", "frodo", "frodo@gmail.com", "Admin", true },
            { "Robin", "robin", "robin@gmail.com", "Admin", true },
            { "Gandalf", "gandalf", "gandalf@gmail.com", "Admin", true },
            { "Aragorn", "aragorn", "aragorn@gmail.com", "Admin", true },
            { "Legolas", "legolas", "legolas@gmail.com", "Admin", true },
            { "Gimli", "gimli", "gimli@gmail.com", "Admin", true },
            { "Boromir", "boromir", "boromir@gmail.com", "Admin", true },
            { "Merry", "merry", "merry@gmail.com", "Admin", true },
            { "Pippin", "pippin", "pippin@gmail.com", "Admin", true },
            { "Samwise", "samwise", "samwise@gmail.com", "Admin", true },
            { "Bilbo", "bilbo", "bilbo@gmail.com", "Admin", true },
            { "Sauron", "sauron", "sauron@gmail.com", "Admin", true },
            { "Gollum", "gollum", "gollum@gmail.com", "Admin", true },
            { "Elrond", "elrond", "elrond@gmail.com", "Admin", true },
            { "Galadriel", "galadriel", "galadriel@gmail.com", "Admin", true },
            { "Saruman", "saruman", "saruman@gmail.com", "Admin", true },
            { "Theoden", "theoden", "theoden@gmail.com", "Admin", true },
            { "Eowyn", "eowyn", "eowyn@gmail.com", "Admin", true },
            { "Faramir", "faramir", "faramir@gmail.com", "Admin", true },
            { "Denethor", "denethor", "denethor@gmail.com", "Admin", true },
            { "Arwen", "arwen", "arwen@gmail.com", "Admin", true },
            { "Bard", "bard", "bard@gmail.com", "Admin", true }
        };
        var fieldsKeys = Arrays.stream(fields.keySet().toArray())
            .map(obj -> (String)obj).toArray(String[]::new);
        gui.createTable(fieldsKeys, data);

        var dataModel = gui.getTableModel();
        // gui.setTableSelectionListener(() -> {
        //     var formFieldMap = extractFormValues(fields);
        //     var overrideData = true;
        //     if (
        //         !formFieldMap.get("Name").isEmpty() ||
        //         !formFieldMap.get("Username").isEmpty() ||
        //         !formFieldMap.get("Email").isEmpty()
        //     ) {
        //          overrideData = JOptionPane.showConfirmDialog(
        //             null, "Are you sure you want to override form fields!",
        //             "Override Comfirmation", JOptionPane.YES_NO_OPTION
        //         ) == 0 ? true : false;
        //     }
        //     if (overrideData) {
        //         var selectedRow = gui.getTableSelectedRow();
        //         ((JTextField)fields.get("Name")).setText(dataModel.getValueAt(selectedRow, 0).toString());
        //         ((JTextField)fields.get("Username")).setText(dataModel.getValueAt(selectedRow, 1).toString());
        //         ((JTextField)fields.get("Email")).setText(dataModel.getValueAt(selectedRow, 2).toString());
        //         ((JComboBox)fields.get("Role")).setSelectedIndex(
        //             Arrays.asList(roles).indexOf(dataModel.getValueAt(selectedRow, 3))
        //         );
        //         ((JCheckBox)fields.get("Status")).setSelected(
        //             (boolean)dataModel.getValueAt(selectedRow, 4)
        //         );
        //     }
        // });
        gui.createFormButton("Add", (e) -> {
            var formFieldMap = extractFormValues(fields);
            if (validateFormValues(formFieldMap, dataModel)) {
                if (findUsername(formFieldMap.get("Username"), dataModel) > -1) {
                    JOptionPane.showMessageDialog(
                        null,
                        "Username already exists: " + formFieldMap.get("Username"),
                        "Error",
                        JOptionPane.WARNING_MESSAGE
                    );
                } else {
                    dataModel.addRow(formFieldMap.values().toArray());
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
                    var values = formFieldMap.values().toArray();
                    for (int col = 0; col < values.length; col++) {
                        dataModel.setValueAt(values[col], rowIndex, col);
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
                    dataModel.removeRow(selectedRow);
                }
            } else {
                JOptionPane.showMessageDialog(
                    null, "Please, select a row to delete.",
                    "Error", JOptionPane.WARNING_MESSAGE
                );
            }
        });
        gui.createFormButton("Clear", (e) -> {
            ((JTextField)fields.get("Name")).setText("");
            ((JTextField)fields.get("Username")).setText("");
            ((JTextField)fields.get("Email")).setText("");
            ((JComboBox)fields.get("Role")).setSelectedIndex(0);
            ((JCheckBox)fields.get("Status")).setSelected(false);
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
        SwingUtilities.invokeLater(Main::start);
    }
}
