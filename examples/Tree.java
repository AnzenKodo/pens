/**
 * To Run Application:
 *      javac Tree.java
 *      java Tree
 */

import javax.swing.UIManager.*;
import javax.swing.*;
import javax.swing.tree.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class Tree {
    static void start() {
        var gui = new GUI("User Management System", 500, 500);

        var parent1 = new DefaultMutableTreeNode("Parent 1");
        var child1_1 = new DefaultMutableTreeNode("Child 1.1");
        var child1_2 = new DefaultMutableTreeNode("Child 1.2");
        parent1.add(child1_1);
        parent1.add(child1_2);

        var parent2 = new DefaultMutableTreeNode("Parent 2");
        var child2_1 = new DefaultMutableTreeNode(new CheckboxNode("Checkbox 1", false));
        var child2_2 = new DefaultMutableTreeNode(new CheckboxNode("Checkbox 2", false));
        parent2.add(child2_1);
        parent2.add(child2_2);

        var parent4 = new DefaultMutableTreeNode("Parent 4");
        var child4_1 = new DefaultMutableTreeNode(new CheckboxNode("Checkbox 5", false));
        var child4_2 = new DefaultMutableTreeNode(new CheckboxNode("Checkbox 4", false));
        parent4.add(child4_1);
        parent4.add(child4_2);

        var parent3 = new DefaultMutableTreeNode("Parent 3");
        String[] items1 = { "Item1 1", "Item1 2", "Item1 3" };
        var child3_1 = new DefaultMutableTreeNode(new ComboboxNode(items1, "Item1 3"));
        String[] items2 = { "Item2 1", "Item2 2", "Item2 3" };
        var child3_2 = new DefaultMutableTreeNode(new ComboboxNode(items2));
        parent3.add(child3_1);
        parent3.add(child3_2);

        var parent5 = new DefaultMutableTreeNode("Parent 5");
        String[] items3 = { "Item3 1", "Item3 2", "Item3 3" };
        var child5_1 = new DefaultMutableTreeNode(new ComboboxNode(items3));
        var child5_2 = new DefaultMutableTreeNode(new ComboboxNode(items3));
        parent5.add(child5_1);
        parent5.add(child5_2);

        var root = new DefaultMutableTreeNode("Root");
        root.add(parent1);
        root.add(parent2);
        root.add(parent4);
        root.add(parent3);
        root.add(parent5);

        JTree tree = new JTree(root);
        for (int i = 0; i < tree.getRowCount(); i++) {
            tree.expandRow(i);
        }
        tree.setEditable(true);
        tree.setCellRenderer(new AdvanceCellRenderer());
        tree.setCellEditor(new AdvanceCellEditor());

        gui.frame.add(new JScrollPane(tree));
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Tree::start);
    }
}

class GUI {
    private boolean DEBUG_BUILD = true;

    private String windowTitle = "GUI Window";
    private int windowWidth = 100;
    private int windowHeight = 100;

    final JFrame frame = new JFrame();

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
        // Setup Look and Feel
        try {
            for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (Exception e) {
        }

        // Setup Main Frame
        frame.setTitle(this.windowTitle);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        frame.setSize(this.windowWidth, this.windowHeight);

        // Esc for Debug build
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
}

class CheckboxNode {
    String name;
    boolean value;

    public CheckboxNode(String name, boolean value) {
        this.name = name;
        this.value = value;
    }

    public String toString() {
        return "CheckboxNode[value: " + value + ", name:" + name + "]";
    }
}

class ComboboxNode {
    String[] items;
    String selected;

    public ComboboxNode(String[] items) {
        this.items = items;
    }

    public ComboboxNode(String[] items, String selected) {
        this.items = items;
        this.selected = selected;
    }

    public String toString() {
        return Arrays.toString(items);
    }
}


class AdvanceCellRenderer implements TreeCellRenderer {
    JLabel label = new JLabel();
    JTextField textfield = new JTextField();
    JComboBox<String> combobox = new JComboBox<>();
    JCheckBox checkbox = new JCheckBox();

    public AdvanceCellRenderer() {
        textfield.setEditable(false);
        textfield.setBorder(null);
        combobox.setEditable(false);
        combobox.setBorder(null);
    }

    public Component getTreeCellRendererComponent(
        JTree tree, Object value,
        boolean selected, boolean expanded, boolean leaf,
        int row, boolean hasFocus
    ) {
        var node = (DefaultMutableTreeNode)value;
        var panel = new JPanel();
        panel.setOpaque(false);
        if(node.getUserObject() instanceof CheckboxNode) {
            var checkboxObj = (CheckboxNode)node.getUserObject();
            checkbox.setSelected(checkboxObj.value);
            textfield.setText(checkboxObj.name);
            panel.add(checkbox);
            panel.add(textfield);
            return panel;
        } else if(node.getUserObject() instanceof ComboboxNode) {
            var comboboxObj = (ComboboxNode)node.getUserObject();
            combobox.removeAllItems();
            for (Object item: comboboxObj.items) {
                combobox.addItem(item.toString());
            }
            if (comboboxObj.selected != null) {
                combobox.setSelectedItem(comboboxObj.selected.toString());
            }
            panel.add(combobox);
            return panel;
        } else {
            label.setText(node.toString());
            panel.add(label);
            return panel;
        }
    }
}

class AdvanceCellEditor extends AbstractCellEditor implements TreeCellEditor, ActionListener {
    JLabel label = new JLabel();
    JTextField textfield = new JTextField();
    JComboBox<String> combobox = new JComboBox<>();
    JCheckBox checkbox = new JCheckBox();
    JComponent editedComponent;
    Object actionObj;

    public AdvanceCellEditor() {
        checkbox.addActionListener(this);
        checkbox.setBorder(null);
        checkbox.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                checkbox.setBorder(BorderFactory.createEmptyBorder(1,1,1,1));
            }
            public void mouseReleased(MouseEvent e) {
                checkbox.setBorder(null);
            }
        });
        combobox.addActionListener(this);
        textfield.addActionListener(this);
        textfield.setBorder(null);
    }

    public Component getTreeCellEditorComponent(
        JTree tree, Object value,
        boolean isSelected, boolean expanded, boolean leaf,
        int row
    ) {
        var node = (DefaultMutableTreeNode)value;
        actionObj = node.getUserObject();
        var panel = new JPanel();
        panel.setOpaque(false);
        if(node.getUserObject() instanceof CheckboxNode) {
            var checkboxObj = (CheckboxNode)actionObj;
            checkbox.setSelected(checkboxObj.value);
            textfield.setText(checkboxObj.name);
            panel.add(checkbox);
            panel.add(textfield);
            return panel;
        } else if(node.getUserObject() instanceof ComboboxNode) {
            var comboboxObj = (ComboboxNode)actionObj;
            combobox.removeAllItems();
            for (Object item: comboboxObj.items) {
                combobox.addItem(item.toString());
            }
            if (comboboxObj.selected != null) {
                combobox.setSelectedItem(comboboxObj.selected.toString());
            }
            panel.add(combobox);
            return panel;
        } else {
            label.setText(node.toString());
            panel.add(label);
            return panel;
        }
    }

    public Object getCellEditorValue() {
        if(editedComponent == textfield)
            ((CheckboxNode)actionObj).name = textfield.getText();
        else if(editedComponent == checkbox)
            ((CheckboxNode)actionObj).value = checkbox.isSelected();
        else if(editedComponent == combobox)
            ((ComboboxNode)actionObj).selected = (String)combobox.getSelectedItem();
        return actionObj;
    }

    public boolean isCellEditable(EventObject event) {
        if (event instanceof MouseEvent) {
            var anEvent = (MouseEvent)event;
            var p = anEvent.getPoint();
            var tree = (JTree)event.getSource();
            var path = tree.getPathForLocation(p.x, p.y);
            var node = (DefaultMutableTreeNode)path.getLastPathComponent();
            int clickCountToStart = (node.getUserObject() instanceof CheckboxNode) ? 1 : 2;
            return anEvent.getClickCount() >= clickCountToStart;
        }
        return true;
    }

    public void actionPerformed(ActionEvent e) {
        editedComponent = (JComponent)e.getSource();
        super.stopCellEditing();
    }
}
