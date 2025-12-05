import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.event.*;
import javax.swing.UIManager.*;
import javax.swing.table.*;
import java.util.stream.*;
import javax.swing.text.*;

public class GUI {
    public boolean DEBUG_BUILD = true;

    public String windowTitle = "GUI Window";
    public int windowWidth = 100;
    public int windowHeight = 100;

    private JFrame frame;
    private JSplitPane contentPanel;
    private JPanel formButtons;
    private JTable table;
    private DefaultTableModel tableModel;

    GUI() {
        init();
    }
    GUI(String title, int width, int height) {
        this.windowTitle = title;
        this.windowWidth = width;
        this.windowHeight = height;
        init();
    }

    private void init() {
        try {
            for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (Exception e) {
        }

        frame = new JFrame(this.windowTitle);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        frame.setSize(this.windowWidth, this.windowHeight);
        ((JComponent) frame.getContentPane()).setBorder(BorderFactory.createEmptyBorder(5, 0, 0, 0));
        if (DEBUG_BUILD) {
            var rootPane = frame.getRootPane();
            Action dispatchClosing = new AbstractAction() {
                public void actionPerformed(ActionEvent event) {
                    frame.dispatchEvent(
                        new WindowEvent(frame, WindowEvent.WINDOW_CLOSING)
                    );
                }
            };
            rootPane.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW)
                .put(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "closeWindow");
            rootPane.getActionMap().put("closeWindow", dispatchClosing);
        }
    }
    public JPanel fieldBuilder(
        Map<String, JComponent> fields, JComponent layout,
        String name, int top, int left, int bottom, int right
    ) {
        var label = new JLabel(name + ":");
        label.setBorder(BorderFactory.createEmptyBorder(top, left, bottom, right));
        label.setLabelFor(fields.get(name));
        var fieldPane = new JPanel();
        fieldPane.setLayout(new BoxLayout(fieldPane, BoxLayout.LINE_AXIS));
        fieldPane.add(label);
        fieldPane.add(fields.get(name));
        layout.add(fieldPane);
        return fieldPane;
    }

    public void createFormFields(Map<String, JComponent> fields) {
        contentPanel = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
        frame.add(contentPanel);

        var formPanel = new JPanel();
        formPanel.setLayout(new BoxLayout(formPanel, BoxLayout.PAGE_AXIS));
        contentPanel.add(formPanel);

        fieldBuilder(fields, formPanel, "Name", 0, 10, 0, 50);
        fieldBuilder(fields, formPanel, "Username", 0, 10, 0, 25);
        fieldBuilder(fields, formPanel, "Email", 0, 10, 0, 52);
        fieldBuilder(fields, formPanel, "Role", 0, 10, 0, 58);
        var statusFieldPane = fieldBuilder(fields, formPanel, "Status", 0, 10, 0, 50);
        statusFieldPane.add(Box.createHorizontalGlue());

        formButtons = new JPanel();
        formButtons.setLayout(new BoxLayout(formButtons, BoxLayout.LINE_AXIS));
        formPanel.add(formButtons);;
    }

    public void createFormButton(String name, ActionListener callback) {
        var button = new JButton(name);
        button.addActionListener(callback);
        formButtons.add(button);
    }

    public void createTable(String[] fieldsNames, Object[][] data) {
        var subContentPanel = new JPanel(new BorderLayout());
        contentPanel.add(subContentPanel);

        // Table ==============================================================
        tableModel = new DefaultTableModel(data, fieldsNames) {
            @Override
            public Class<?> getColumnClass(int columnIndex) {
                if (columnIndex == 4) {
                    return Boolean.class;
                }else {
                    return super.getColumnClass(columnIndex);
                }
            }
        };
        table = new JTable(tableModel);
        subContentPanel.add(new JScrollPane(table));
        var tableSorter = new TableRowSorter<>(tableModel);
        table.setRowSorter(tableSorter);

        String[] roles = { "Admin", "User", "Guest" };
        JComboBox<String> rolesCombobox = new JComboBox<>(roles);
        table.getColumnModel().getColumn(3).setCellEditor(new DefaultCellEditor(rolesCombobox));

        // Search Area ========================================================
        var searchPanel = new JPanel(new GridBagLayout());
        subContentPanel.add(searchPanel, BorderLayout.PAGE_START);
        var gbc = new GridBagConstraints();
        gbc.insets = new Insets(3, 0, 0, 0);

        // Lable ===
        var searchLabel = new JLabel("  Search:");
        gbc.gridx = 0; gbc.weightx = 0; gbc.fill = GridBagConstraints.NONE;
        searchPanel.add(searchLabel, gbc);

        // Searchbar ====
        var searchField = new JTextField();
        searchField.setEditable(true);
        gbc.gridx = 1; gbc.weightx = 1; gbc.fill = GridBagConstraints.HORIZONTAL;
        searchPanel.add(searchField, gbc);

        // Filter ===
        var filterNames = new Vector<String>(Arrays.asList(fieldsNames));
        filterNames.add(0, "All");
        var filter = new JComboBox<String>(filterNames);
        gbc.gridx = 2; gbc.weightx = 0; gbc.fill = GridBagConstraints.NONE;
        searchPanel.add(filter, gbc);

        // Events Handle ======================================================
        Runnable filterLogic = () -> {
            var searchText = searchField.getText().toLowerCase();
            var filterSelectedIndex = filter.getSelectedIndex() - 1;

            if (searchText.isEmpty()) {
                tableSorter.setRowFilter(null);
            } else {
                if (searchText.length() == 0) {
                    tableSorter.setRowFilter(null);
                } else {
                    if (filterSelectedIndex > -1) {
                        tableSorter.setRowFilter(
                            RowFilter.regexFilter("(?i)" + searchText, filterSelectedIndex)
                        );
                    } else {
                        tableSorter.setRowFilter(RowFilter.regexFilter("(?i)" + searchText));
                    }
                }
                tableSorter.sort();
            }
        };

        searchField.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                filterLogic.run();
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                filterLogic.run();
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                filterLogic.run();
            }
        });
    }

    public ArrayList<String> getAllColValues(int index) {
        ArrayList<String> columnValues = new ArrayList<String>();
        for (int row = 0; row < tableModel.getRowCount(); row++) {
            var value = tableModel.getValueAt(row, index).toString();
            columnValues.add(value);
        }
        return columnValues;
    }
    public void setTableSelectionListener(Runnable callback) {
        table.addMouseListener(new MouseAdapter() {
            @Override
                public void mouseClicked(MouseEvent e) {
                    if (e.getClickCount() == 2) {
                        callback.run();
                    }
                }
        });
    }
    public int getTableSelectedRow() {
        return table.getSelectedRow();
    }
    public String getTableColValue(int row, int col) {
        return table.getValueAt(row, col).toString();
    }
    public DefaultTableModel getTableModel() {
        return tableModel;
    }

    public class TextField extends JTextField {
        private int limit;

        public TextField(int limit) {
            super();
            this.limit = limit;
        }

        public TextField(int limit, int columns) {
            super(columns);
            this.limit = limit;
        }

        @Override
        protected Document createDefaultModel() {
            return new LimitDocument();
        }

        private class LimitDocument extends PlainDocument {
            @Override
            public void insertString(int offset, String str, AttributeSet attr)
                    throws BadLocationException {
                if (str == null) return;
                if ((getLength() + str.length()) <= limit) {
                    super.insertString(offset, str, attr);
                }
            }
        }
    }
}
