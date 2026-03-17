import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.sql.*;
import java.time.LocalDate;
import java.time.format.DateTimeParseException;
import java.time.temporal.TemporalAdjusters;

public class DatabaseUI extends JFrame {

    public procedures proc = new procedures();
    private final JPanel mainOptionsPanel;
    private final JPanel subOptionsPanel;
    private final JPanel actionPanel;
    private boolean payrollFlag=true;
    private Connection conn;

    public DatabaseUI() {
        super("University Payroll System");
        setSize(900, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JPanel topPanel = new JPanel();
        topPanel.setBorder(BorderFactory.createEtchedBorder());


        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new GridLayout(1, 3, 10, 10));
        centerPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        mainOptionsPanel = new JPanel(new GridLayout(10, 1, 5, 5));
        mainOptionsPanel.setBackground(Color.WHITE);

        subOptionsPanel = new JPanel(new GridLayout(10, 1, 5, 5));
        subOptionsPanel.setBackground(Color.WHITE);
        subOptionsPanel.setBorder(BorderFactory.createLineBorder(Color.GRAY));

        actionPanel = new JPanel(new FlowLayout());
        actionPanel.setBackground(Color.WHITE);
        actionPanel.setBorder(BorderFactory.createLineBorder(Color.GRAY));

        setupMainMenu();

        centerPanel.add(mainOptionsPanel);
        centerPanel.add(subOptionsPanel);
        centerPanel.add(actionPanel);

        add(centerPanel, BorderLayout.CENTER);

        setVisible(true);
        super.setExtendedState(JFrame.MAXIMIZED_BOTH);
    }


    private void setupMainMenu() {
        addButton(mainOptionsPanel, "Manage Employees", e -> showEmployeeOptions());
        addButton(mainOptionsPanel, "Manage Salaries", e -> showSalaryOptions());
        addButton(mainOptionsPanel, "Run Payroll", e -> showPayrollOptions());
        addButton(mainOptionsPanel, "Queries", e -> showQueryOptions());

    }

    private void addButton(JPanel panel, String text, ActionListener action) {
        JButton btn = new JButton(text);
        btn.setPreferredSize(new Dimension(400,100));
        btn.setFont(new Font("Serif",Font.BOLD,18));
        btn.addActionListener(action);
        panel.add(btn);
    }


    private void showEmployeeOptions() {
        subOptionsPanel.removeAll();
        actionPanel.removeAll();

        addButton(subOptionsPanel, "Hire New Employee", e -> showHireForm());
        addButton(subOptionsPanel, "Edit / Search", e -> showSearchForm());
        addButton(subOptionsPanel, "Fire / Retire", e -> showFireForm());

        refreshPanels();
    }

    private void showSalaryOptions() {
        subOptionsPanel.removeAll();
        actionPanel.removeAll();

        JPanel listPanel = new JPanel(new GridLayout(4, 1, 10, 10));
        listPanel.setBorder(BorderFactory.createEmptyBorder(20, 40, 20, 40));

        listPanel.add(createCategoryRow("Permanent Administrative Staff", "Admin", "Perm"));

        listPanel.add(createCategoryRow("Contract Administrative Staff", "Admin", "Contract"));

        listPanel.add(createCategoryRow("Permanent Teaching Staff", "Teaching", "Perm"));

        listPanel.add(createCategoryRow("Contract Teaching Staff", "Teaching", "Contract"));

        actionPanel.add(listPanel);
        refreshPanels();
    }

    private JPanel createCategoryRow(String title, String category, String status) {
        JPanel row = new JPanel(new BorderLayout());
        row.setBorder(BorderFactory.createLineBorder(Color.GRAY, 1));
        row.setBackground(Color.WHITE);
        row.setPreferredSize(new Dimension(500, 80));

        JLabel label = new JLabel("  " + title);
        label.setFont(new Font("SansSerif", Font.BOLD, 16));

        JButton editBtn = new JButton("Edit Rules");
        editBtn.setPreferredSize(new Dimension(120, 40));

        editBtn.addActionListener(e -> openSalaryEditor(title, category, status));

        row.add(label, BorderLayout.CENTER);
        row.add(editBtn, BorderLayout.EAST);

        return row;
    }

    private void openSalaryEditor(String title, String category, String status) {
        actionPanel.removeAll();

        JPanel header = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JLabel headerLbl = new JLabel("Editing Rules: " + title);
        headerLbl.setFont(new Font("Serif", Font.BOLD, 20));
        header.add(headerLbl);

        JButton backBtn = new JButton("<< Back");
        backBtn.addActionListener(e -> showSalaryOptions());
        header.add(Box.createHorizontalStrut(20));
        header.add(backBtn);

        JPanel formPanel = new JPanel(new GridLayout(0, 2, 10, 10));
        formPanel.setBorder(BorderFactory.createTitledBorder("Payroll Configuration"));

        String[] rules = proc.get_salaries_benefits(category, status);
        if (rules == null || rules.length < 6) {
            rules = new String[]{"0", "0", "0", "0", "0", "0"};
        }

        // str[0]=Years, str[1]=Research, str[2]=Library, str[3]=Child, str[4]=Spouse, str[5]=Base
        JTextField yearsField = new JTextField(rules[0]);
        JTextField resField   = new JTextField(rules[1]);
        JTextField libField   = new JTextField(rules[2]);
        JTextField childField = new JTextField(rules[3]);
        JTextField spouseField= new JTextField(rules[4]);
        JTextField baseField  = new JTextField(rules[5]);

        String originalSalary = rules[5];

        System.out.println(rules[5]+" "+rules[1]+" "+rules[2]+" "+rules[3]+" "+rules[4]+" "+rules[0]);



        if (status.equals("Perm")) {
            formPanel.add(new JLabel("Base Salary (€):"));
            formPanel.add(baseField);
        }

        if (status.equals("Perm")) {
            formPanel.add(new JLabel("Years Service Increase (%):"));
            formPanel.add(yearsField);
        }

        if (category.equals("Teaching") && status.equals("Perm")) {
            formPanel.add(new JLabel("Research Allowance (€):"));
            formPanel.add(resField);
        }

        if (category.equals("Teaching") && status.equals("Contract")) {
            formPanel.add(new JLabel("Library Allowance (€):"));
            formPanel.add(libField);
        }

        formPanel.add(new JLabel("Child Allowance (%):"));
        formPanel.add(childField);

        formPanel.add(new JLabel("Spouse Allowance (%):"));
        formPanel.add(spouseField);

        JButton saveBtn = new JButton("Save Changes");
        formPanel.add(new JLabel(""));
        formPanel.add(saveBtn);

        saveBtn.addActionListener(ev -> {
            try {
                double child = Double.parseDouble(childField.getText().trim());
                double spouse = Double.parseDouble(spouseField.getText().trim());

                double base = 0;
                if (status.equals("Perm")) {
                    base = Double.parseDouble(baseField.getText().trim());
                } else {
                    base = Double.parseDouble(originalSalary);
                }

                double years = 0;
                if (status.equals("Perm")) {
                    years = Double.parseDouble(yearsField.getText().trim());
                }

                double res = 0;
                if (category.equals("Teaching") && status.equals("Perm")) {
                    res = Double.parseDouble(resField.getText().trim());
                }

                double lib = 0;
                if (category.equals("Teaching") && status.equals("Contract")) {
                    lib = Double.parseDouble(libField.getText().trim());
                }

                System.out.println(base+" "+res+" "+lib+" "+child+" "+spouse+" "+years);

                //proc.updatePayrollRules(category, status, base, res, lib, child, spouse, years);
                proc.Change_salaries_benefits(category, status, years, lib, child, spouse, base, res);

                JOptionPane.showMessageDialog(this, "Rules updated for " + title);
                showSalaryOptions();

            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Error: Invalid numbers.");
            } catch (Exception ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage());
            }
        });

        JPanel mainContainer = new JPanel(new BorderLayout());
        mainContainer.add(header, BorderLayout.NORTH);
        mainContainer.add(formPanel, BorderLayout.CENTER);

        actionPanel.add(mainContainer);
        refreshPanels();
    }


    private void showPayrollOptions() {
        subOptionsPanel.removeAll();
        actionPanel.removeAll();

        addButton(subOptionsPanel, "Execute Monthly Payroll", e -> {

            LocalDate date = LocalDate.now();
            int lastDayOfMonth = date.with(TemporalAdjusters.lastDayOfMonth()).getDayOfMonth();
            if (lastDayOfMonth != date.getDayOfMonth())
            {
                JOptionPane.showMessageDialog(this, "Payroll can be executed only at the end of the month!");
                return;
            }

            if (!payrollFlag) {
                JOptionPane.showMessageDialog(this, "Payroll has already been executed for this session!");
                return;
            }

            String[][] rawData = proc.calculateAndSavePayroll();

            payrollFlag = false;

            if (rawData.length == 0) {
                JOptionPane.showMessageDialog(this, "No payments were generated (or Database Error).");
                return;
            }

            String[] columnNames = {"Name", "Category", "Status", "Amount Paid"};
            String[][] filteredData = new String[rawData.length][4];

            for (int i = 0; i < rawData.length; i++) {
                filteredData[i][0] = rawData[i][0];
                filteredData[i][1] = rawData[i][1];
                filteredData[i][2] = rawData[i][2];
                filteredData[i][3] = rawData[i][rawData[i].length - 1];
            }

            JFrame reportFrame = new JFrame("Payroll Report");
            reportFrame.setSize(600, 500);
            reportFrame.setLocationRelativeTo(this);

            JTable table = new JTable(filteredData, columnNames);
            table.setRowHeight(25);
            table.setFont(new Font("SansSerif", Font.PLAIN, 14));
            table.getTableHeader().setFont(new Font("SansSerif", Font.BOLD, 14));

            JScrollPane scrollPane = new JScrollPane(table);
            reportFrame.add(scrollPane);

            reportFrame.setVisible(true);
        });

        refreshPanels();
    }

    private void showQueryOptions() {
        subOptionsPanel.removeAll();
        actionPanel.removeAll();

        addButton(subOptionsPanel, "Payroll Status by Category", e -> {
            String[] columns = {"ID", "Category", "Status", "Name", "Total Paid"};
            String[][] data = proc.getPayrollStatusByCategory();
            showResultTable("Payroll Status Report", columns, data);
        });

        addButton(subOptionsPanel, "Max, Min, Avg Salary", e -> {
            String[] columns = {"Category", "Status", "Max Salary", "Min Salary", "Avg Salary"};
            String[][] data = proc.getSalaryStats();
            showResultTable("Salary Statistics", columns, data);
        });

        addButton(subOptionsPanel, "Avg Increase Over Time", e -> {
            String[] columns = {"Payment Date", "Average Salary Paid"};
            String[][] data = proc.getAverageSalaryTrends();
            showResultTable("Salary Trends Over Time", columns, data);
        });

        addButton(subOptionsPanel, "Specific Employee Details", e -> {
            String input = JOptionPane.showInputDialog(this, "Enter Employee ID:");
            if (input != null && !input.trim().isEmpty()) {
                try {
                    int empId = Integer.parseInt(input.trim());
                    String[] columns = {"ID", "Name", "Category", "Status", "Pay Date", "Amount"};
                    String[][] data = proc.getSpecificEmployeeHistory(empId);

                    if (data.length == 0) {
                        JOptionPane.showMessageDialog(this, "No history found for ID: " + empId);
                    } else {
                        showResultTable("Employee History: " + empId, columns, data);
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(this, "Error: Invalid ID format.");
                }
            }
        });

        addButton(subOptionsPanel, "Total Payroll Cost", e -> {
            String[] columns = {"Category", "Status", "Total Cost"};
            String[][] data = proc.getTotalCostByCategory();
            showResultTable("Total Cost Report", columns, data);
        });

        refreshPanels();
    }

    private void showResultTable(String title, String[] columns, String[][] data) {
        if (data == null || data.length == 0) {
            JOptionPane.showMessageDialog(this, "No data available for " + title);
            return;
        }

        JFrame frame = new JFrame(title);
        frame.setSize(700, 500);
        frame.setLocationRelativeTo(this);

        JTable table = new JTable(data, columns);
        table.setRowHeight(25);
        table.setFont(new Font("SansSerif", Font.PLAIN, 14));
        table.getTableHeader().setFont(new Font("SansSerif", Font.BOLD, 14));

        JScrollPane scrollPane = new JScrollPane(table);
        frame.add(scrollPane);

        frame.setVisible(true);
    }




    private void showHireForm() {
        actionPanel.removeAll();

        JTextField nameInput = new JTextField();
        JComboBox<String> categoryInput = new JComboBox<>(new String[]{"Admin", "Teaching"});
        JComboBox<String> statusInputMarriage = new JComboBox<>(new String[]{"Unmarried","Married"});
        JTextField childrenCount = new JTextField();
        JTextField childrenAges = new JTextField();
        JComboBox<String> statusInput = new JComboBox<>(new String[]{"Perm", "Contract"});
        JTextField department = new JTextField();
        JTextField date = new JTextField();
        JTextField contractDate = new JTextField();
        JTextField address = new JTextField();
        JTextField phone = new JTextField();
        JTextField bankAccount = new JTextField();
        JTextField bankName = new JTextField();
        JTextField contractSalary = new JTextField();

        JPanel form = new JPanel(new GridLayout(14, 2, 5, 5));

        form.add(new JLabel("Name:"));
        form.add(nameInput);
        form.add(new JLabel("Marriage Status:"));
        form.add(statusInputMarriage);
        form.add(new JLabel("Children count"));
        form.add(childrenCount);
        form.add(new JLabel("Children ages (X-X-X)"));
        form.add(childrenAges);
        form.add(new JLabel("Category:"));
        form.add(categoryInput);
        form.add(new JLabel("Status"));
        form.add(statusInput);
        form.add(new JLabel("Department"));
        form.add(department);
        form.add(new JLabel("Date (YYYY-MM-DD)"));
        form.add(date);
        form.add(new JLabel("Contract date"));
        form.add(contractDate);
        form.add(new JLabel("Address"));
        form.add(address);
        form.add(new JLabel("Phone"));
        form.add(phone);
        form.add(new JLabel("Bank account"));
        form.add(bankAccount);
        form.add(new JLabel("Bank name"));
        form.add(bankName);
        form.add(new JLabel("Contract salary"));
        form.add(contractSalary);



        statusInput.addActionListener(event -> {
            String selected = (String) statusInput.getSelectedItem();
            if ("Contract".equals(selected)) {
                contractDate.setEnabled(true);
                contractDate.setBackground(Color.WHITE);
                contractSalary.setEnabled(true);
                contractSalary.setBackground(Color.WHITE);
            } else {
                contractDate.setEnabled(false);
                contractDate.setBackground(Color.LIGHT_GRAY);
                contractDate.setText(null);
                contractSalary.setEnabled(false);
                contractSalary.setBackground(Color.LIGHT_GRAY);
                contractSalary.setText(null);
            }
        });

        contractDate.setEnabled(false);
        contractSalary.setEnabled(false);
        contractSalary.setBackground(Color.LIGHT_GRAY);
        contractDate.setBackground(Color.LIGHT_GRAY);

        JButton saveBtn = new JButton("Save");

        saveBtn.addActionListener(e -> {
            try {
                String nameStr = nameInput.getText().trim();
                String categoryStr = (String) categoryInput.getSelectedItem();
                String statusStr = (String) statusInput.getSelectedItem();
                String marriageStr = (String) statusInputMarriage.getSelectedItem();
                String childrenAgStr = childrenAges.getText().trim();
                String departStr = department.getText().trim();
                String dateStr = date.getText().trim();
                String contractDateStr = contractDate.getText().trim();
                String addressStr = address.getText().trim();
                String phoneStr = phone.getText().trim();
                String bankAccountStr = bankAccount.getText().trim();
                String bankNameStr = bankName.getText().trim();

                if (nameStr.isEmpty()) {
                    JOptionPane.showMessageDialog(this, "Error: Name cannot be empty.");
                    return;
                }

                if (addressStr.isEmpty() || phoneStr.isEmpty() || bankAccountStr.isEmpty() ||
                        bankNameStr.isEmpty() || departStr.isEmpty()) {
                    JOptionPane.showMessageDialog(this, "Error: All fields (Address, Phone, Bank, Dept) are mandatory.");
                    return;
                }

                if (nameStr.matches(".*\\d.*")) {
                    JOptionPane.showMessageDialog(this, "Error: Name cannot contain numbers.");
                    return;
                }

                if (!phoneStr.matches("\\d+")) {
                    JOptionPane.showMessageDialog(this, "Error: Phone number must contain digits only.");
                    return;
                }


                LocalDate parsedDate = null;
                try {
                    parsedDate = LocalDate.parse(dateStr);
                } catch (DateTimeParseException ex) {
                    JOptionPane.showMessageDialog(this, "Λάθος format ημερομηνίας (YYYY-MM-DD)");
                    return;
                }

                if (parsedDate.getDayOfMonth() != 1) {
                    JOptionPane.showMessageDialog(this, "Η πρόσληψη πρέπει να γίνεται την 1η του μήνα.");
                    return;
                }

                if (parsedDate.isBefore(LocalDate.now())) {
                    JOptionPane.showMessageDialog(this, "Σφάλμα: Δεν γίνεται να δοθεί ημερομηνία αναδρομικά.");
                    return;
                }

                if (statusStr.equals("Contract")) {
                    if (contractDateStr.isEmpty() || !contractDateStr.matches("\\d{4}-\\d{2}-\\d{2}")) {
                        JOptionPane.showMessageDialog(this, "Error: Contract employees must have a valid Contract Date (YYYY-MM-DD).");
                        return;
                    }

                    LocalDate parsedContractDate = null;
                    try {
                        parsedContractDate = LocalDate.parse(contractDateStr);
                    } catch (DateTimeParseException ex) {
                        JOptionPane.showMessageDialog(this, "Error: Invalid Contract Date format.");
                        return;
                    }

                    LocalDate validDate6Months = parsedDate.plusMonths(6);
                    LocalDate validDate12Months = parsedDate.plusMonths(12);

                    if (!parsedContractDate.equals(validDate6Months) && !parsedContractDate.equals(validDate12Months)) {
                        JOptionPane.showMessageDialog(this,
                                "Error: Contract duration must be exactly 6 or 12 months from the hire date.\n" +
                                        "Valid dates would be: " + validDate6Months + " or " + validDate12Months);
                        return;
                    }
                }

                int childrenCountInt = 0;
                if (!childrenCount.getText().trim().isEmpty()) {
                    childrenCountInt = Integer.parseInt(childrenCount.getText().trim());
                }

                if (childrenCountInt > 0) {
                    if (childrenAgStr.isEmpty()) {
                        JOptionPane.showMessageDialog(this, "Error: You entered " + childrenCountInt + " children, but no ages.");
                        return;
                    }

                    String[] agesArray = childrenAgStr.split("-");

                    if (agesArray.length != childrenCountInt) {
                        JOptionPane.showMessageDialog(this,
                                "Error: Age format mismatch.\n" +
                                        "For " + childrenCountInt + " children, you must provide exactly " + childrenCountInt + " ages separated by dashes.\n" +
                                        "Example: 12-5-8");
                        return;
                    }

                    for (String age : agesArray) {
                        try {
                            Integer.parseInt(age.trim());
                        } catch (NumberFormatException g) {
                            JOptionPane.showMessageDialog(this, "Error: Invalid age found ('" + age + "'). Use numbers only.");
                            return;
                        }
                    }
                }

                double contractSalaryVal = 0.0;
                if (!contractSalary.getText().trim().isEmpty()) {
                    contractSalaryVal = Double.parseDouble(contractSalary.getText().trim());
                }

                if (!statusStr.equals("Contract")) {
                    contractDateStr = null;
                }

                proc.hireEmployee(nameStr, marriageStr, childrenCountInt,
                        childrenAgStr, categoryStr, statusStr,
                        departStr, dateStr, contractDateStr, addressStr,
                        phoneStr, bankAccountStr, bankNameStr, contractSalaryVal);

                JOptionPane.showMessageDialog(this, "Employee Saved Successfully!");

            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Error: Please enter valid numbers for Children Count and Salary.");
            } catch (Exception ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(this, "Database Error: " + ex.getMessage());
            }
        });

        actionPanel.add(form);
        actionPanel.add(saveBtn);
        refreshPanels();
    }

    private void showSearchForm() {
        actionPanel.removeAll();

        JPanel searchBarPanel = new JPanel();
        searchBarPanel.add(new JLabel("Enter Employee ID to Edit:"));
        JTextField searchIdField = new JTextField(10);
        JButton searchBtn = new JButton("Search & Edit");
        searchBarPanel.add(searchIdField);
        searchBarPanel.add(searchBtn);

        actionPanel.add(searchBarPanel);


        JPanel formPanel = new JPanel(new GridLayout(15, 2, 5, 5));
        actionPanel.add(formPanel);

        searchBtn.addActionListener(e -> {
            String idStr = searchIdField.getText().trim();
            if(!idStr.matches("\\d+")) {
                JOptionPane.showMessageDialog(this, "Please enter a numeric ID.");
                return;
            }

            int idToSearch = Integer.parseInt(idStr);

            String[] data = proc.get_employee_details(idToSearch);
            /*for(int i=0;i<data.length;i++){
                System.out.println("Data at:"+i+" is:"+data[i]);
            }*/

            if (data == null) {
                JOptionPane.showMessageDialog(this, "Employee not found!");
                formPanel.removeAll();
                refreshPanels();
                return;
            }

            formPanel.removeAll();

            JTextField nameF = new JTextField(data[0]);
            JComboBox<String> catBox = new JComboBox<>(new String[]{"Admin", "Teaching"});
            catBox.setSelectedItem(data[4]);

            JComboBox<String> statBox = new JComboBox<>(new String[]{"Perm", "Contract"});
            statBox.setSelectedItem(data[5]);

            JComboBox<String> marBox = new JComboBox<>(new String[]{"Unmarried", "Married"});
            marBox.setSelectedItem(data[1]);

            JTextField childCountF = new JTextField(data[2]);
            JTextField childAgesF = new JTextField(data[3]);
            JTextField deptF = new JTextField(data[6]);
            JTextField dateF = new JTextField(data[7]);
            JTextField conDateF = new JTextField(data[8]);
            JTextField addrF = new JTextField(data[9]);
            JTextField phoneF = new JTextField(data[10]);
            JTextField bankF = new JTextField(data[11]);
            JTextField bankNameF = new JTextField(data[12]);
            JTextField salF = new JTextField(data[13]);


            formPanel.add(new JLabel("Name:"));
            formPanel.add(nameF);
            formPanel.add(new JLabel("Category:"));
            formPanel.add(catBox);
            formPanel.add(new JLabel("Status:"));
            formPanel.add(statBox);
            formPanel.add(new JLabel("Marital:"));
            formPanel.add(marBox);
            formPanel.add(new JLabel("Children:"));
            formPanel.add(childCountF);
            formPanel.add(new JLabel("Ages:"));
            formPanel.add(childAgesF);
            formPanel.add(new JLabel("Dept:"));
            formPanel.add(deptF);
            formPanel.add(new JLabel("Hire Date:"));
            formPanel.add(dateF);
            formPanel.add(new JLabel("Contract End:"));
            formPanel.add(conDateF);
            formPanel.add(new JLabel("Address:"));
            formPanel.add(addrF);
            formPanel.add(new JLabel("Phone:"));
            formPanel.add(phoneF);
            formPanel.add(new JLabel("Bank Acc:"));
            formPanel.add(bankF);
            formPanel.add(new JLabel("Bank Name:"));
            formPanel.add(bankNameF);
            formPanel.add(new JLabel("Salary:"));
            formPanel.add(salF);

            dateF.setEditable(false);
            conDateF.setEditable(false);
            salF.setEditable(false);
            dateF.setBackground(Color.LIGHT_GRAY);
            conDateF.setBackground(Color.LIGHT_GRAY);
            salF.setBackground(Color.LIGHT_GRAY);

            JButton updateBtn = new JButton("Save Changes");
            formPanel.add(new JLabel(""));
            formPanel.add(updateBtn);



            updateBtn.addActionListener(ev -> {

                try {
                    int kids = Integer.parseInt(childCountF.getText());
                    String sal = salF.getText();

                    proc.Change_employee_details(
                            idToSearch,                           // empId
                            nameF.getText(),                      // newname
                            (String) marBox.getSelectedItem(),    // newmaritalstatus
                            kids,                                 // newchildrencount
                            childAgesF.getText(),                 // newchildren_ages
                            (String) catBox.getSelectedItem(),    // newcategory
                            (String) statBox.getSelectedItem(),   // newstatus
                            deptF.getText(),                      // newdepartment
                            addrF.getText(),                      // newaddress
                            phoneF.getText(),                     // newphone
                            bankF.getText(),                      // newbank_account
                            bankNameF.getText(),                  // newbank_name
                            dateF.getText(),                      // newhire_date
                            conDateF.getText(),                   // newcontract_date
                            sal                                   // newcontract_salary
                    );
                    JOptionPane.showMessageDialog(this, "Employee Updated Successfully!");

                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            });

            refreshPanels();
        });

        refreshPanels();
    }

    private void showFireForm() {
        actionPanel.removeAll();

        JLabel label = new JLabel("Fire Employee (ID):");
        JTextField idInput = new JTextField(10);
        JButton deleteBtn = new JButton("Delete");

        deleteBtn.addActionListener(e -> {
            String idStr = idInput.getText().trim();

            if (idStr.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Error: Please enter an ID.");
                return;
            }

            if (!idStr.matches("\\d+")) {
                JOptionPane.showMessageDialog(this, "Error: ID must be a number.");
                return;
            }

            int id = Integer.parseInt(idStr);
            boolean check = proc.fireEmployee(id);
            if(check){
                JOptionPane.showMessageDialog(this, "Employee paid and fired Successfully!");
            }else{
                JOptionPane.showMessageDialog(this, "Employee could not be fired");
            }

        });

        actionPanel.add(label);
        actionPanel.add(idInput);
        actionPanel.add(deleteBtn);

        refreshPanels();
    }

    private void refreshPanels() {
        subOptionsPanel.revalidate();
        subOptionsPanel.repaint();
        actionPanel.revalidate();
        actionPanel.repaint();
    }


}