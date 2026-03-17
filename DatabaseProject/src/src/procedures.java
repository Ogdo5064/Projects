import java.math.BigDecimal;
import java.sql.*;
import java.time.LocalDate;
import java.time.temporal.TemporalAdjusters;
import java.util.ArrayList;
import java.util.List;

public class procedures
{
    DatabaseManager dm = new DatabaseManager();

    private final String url = dm.get_url();
    private final String user = dm.get_user();
    private final String password = dm.get_password();



    public void hireEmployee(String name, String maritalStatus, int childrenCount,
                             String childrenAges, String category, String status,
                             String department, String hire_date,String contract_date,
                             String address, String phone, String bank_account, String bank_name,double contract_salary)
    {
        LocalDate today = LocalDate.now();
        LocalDate date;
        System.out.println(hire_date);
        date = LocalDate.parse(hire_date);

        if (date.getDayOfMonth() != 1)
        {
            return;
        }
        if (date.isBefore(today))
        {
            System.out.println("Σφαλμα δεν γινεται να δοθει ημερομηνια αναδρομικα");
            return;
        }
        String hire = "INSERT INTO Employee_Data " +
                "(name, marital_status, children_count, children_ages, category, status, " +
                "department, hire_date,contract_date, address, phone, bank_account, bank_name,contract_salary) " +
                "VALUES (?,?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

        try (Connection conn = DriverManager.getConnection(url,user,password);
             PreparedStatement pstmt = conn.prepareStatement(hire))
        {
            pstmt.setString(1, name);
            pstmt.setString(2, maritalStatus);
            pstmt.setInt(3, childrenCount);
            pstmt.setString(4, childrenAges);
            pstmt.setString(5, category);
            pstmt.setString(6, status);
            pstmt.setString(7, department);
            pstmt.setString(8, hire_date);
            pstmt.setString(9, contract_date);
            pstmt.setString(10, address);
            pstmt.setString(11, phone);
            pstmt.setString(12, bank_account);
            pstmt.setString(13, bank_name);
            pstmt.setDouble(14, contract_salary);

            int rows = pstmt.executeUpdate();
            if (rows > 0) System.out.println("Correct!!");

        }
        catch (SQLException e) {
            System.out.println("Σφάλμα: " + e.getMessage());
        }

    }

    public String[] get_employee_details(int empId)
    {
        String sql = "select * from Employee_Data where emp_id = ?";
        String[] details = new String[14];
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setInt(1, empId);

            try (ResultSet rs = pstmt.executeQuery()) {

                if (rs.next()) {

                    details[0] = rs.getString("name");
                    details[1] = rs.getString("marital_status");
                    details[2] = String.valueOf(rs.getInt("children_count"));
                    details[3] = rs.getString("children_ages");
                    details[4] = rs.getString("category");
                    details[5] = rs.getString("status");
                    details[6] = rs.getString("department");
                    details[7] = rs.getString("hire_date");

                    //java.sql.Date cDate = rs.getDate("contract_date");
                    //details[8] = (cDate != null) ? cDate.toString() : "";
                    details[8] = rs.getString("contract_date");

                    details[9] = rs.getString("address");
                    details[10] = rs.getString("phone");
                    details[11] = rs.getString("bank_account");
                    details[12] = rs.getString("bank_name");
                    details[13] = String.valueOf(rs.getDouble("contract_salary"));

                    System.out.println("Βρεθηκε ο υπαλληλος");
                    return details;
                } else {
                    System.out.println("Δεν βρέθηκε υπάλληλος");
                    return null;
                }
            }

        } catch (SQLException e) {
            System.out.println("Σφάλμα δεν βρεθηκε ο υπαλληλος " + e.getMessage());
            return null;
        }

    }

    public void Change_employee_details(int empId, String newname, String newmaritalstatus,
                                        int newchildrencount,String newchildren_ages,String newcategory,
                                        String newstatus,String newdepartment,
                                        String newaddress, String newphone,
                                        String newbank_account,String newbank_name,String newhire_date,
                                        String newcontract_date,String newcontract_salary)
    {
        String sql = "UPDATE Employee_Data SET " +
                "name = ?, " +
                "marital_status = ?, " +
                "children_count = ?, " +
                "children_ages = ?, " +
                "category = ?, " +
                "status = ?, " +
                "department = ?, " +
                "hire_date = ?, " +
                "contract_date = ?, " +
                "address = ?, " +
                "phone = ?, " +
                "bank_account = ?, " +
                "bank_name = ?, " +
                "contract_salary = ? " +
                "WHERE emp_id = ?";


        try (Connection conn = DriverManager.getConnection(url,user,password);
             PreparedStatement pstmt = conn.prepareStatement(sql))
        {
            pstmt.setString(1, newname);
            pstmt.setString(2, newmaritalstatus);
            pstmt.setInt(3, newchildrencount);
            pstmt.setString(4, newchildren_ages);
            pstmt.setString(5, newcategory);
            pstmt.setString(6, newstatus);
            pstmt.setString(7, newdepartment);

            try {
                pstmt.setDate(8, java.sql.Date.valueOf(newhire_date));
            } catch (Exception e) {
                System.out.println("Λάθος ημερομηνία πρόσληψης.");
                throw e;
            }

            if (newcontract_date == null || newcontract_date.trim().isEmpty()) {
                pstmt.setNull(9, java.sql.Types.DATE);
            } else {
                try {
                    pstmt.setDate(9, java.sql.Date.valueOf(newcontract_date));
                } catch (Exception e) {
                    System.out.println("Λάθος ημερομηνία σύμβασης -> NULL.");
                    pstmt.setNull(9, java.sql.Types.DATE);
                }
            }
            pstmt.setString(10, newaddress);
            pstmt.setString(11, newphone);
            pstmt.setString(12, newbank_account);
            pstmt.setString(13, newbank_name);

            if (newcontract_salary == null || newcontract_salary.trim().isEmpty()) {
                pstmt.setBigDecimal(14, BigDecimal.ZERO);
            } else {
                try {
                    String salaryStr = newcontract_salary.replace(",", ".");

                    pstmt.setBigDecimal(14, new BigDecimal(salaryStr));

                } catch (NumberFormatException e) {
                    System.out.println("Λάθος format μισθού. Ορίστηκε ως 0.");
                    pstmt.setBigDecimal(14, BigDecimal.ZERO);
                }
            }
            pstmt.setInt(15, empId);


            int rows = pstmt.executeUpdate();
            if (rows == 1) {
                System.out.println("Βρεθηκε ο υπαλληλος emp_id:"+empId);
            } else {
                System.out.println("Δεν βρέθηκε υπάλληλος με αυτό το ID.");
            }
        }
        catch (SQLException e)
        {
            System.out.println("Σφαλμα κατά την ενημέρωση: " + e.getMessage());
        }
    }



    public void Change_salaries_benefits(String category, String status, double newyears_of_service,
                                         double newlibrary_allowance, double newchild_allowance,
                                         double newspouse_allowance, double newbase_salary,
                                         double newresearch_allowance) {

        String selectSql = "SELECT * FROM Payroll_Data WHERE category = ? AND status = ?";

        String updatesql = "UPDATE Payroll_Data SET " +
                "years_of_service = ?, " +
                "research_allowance = ?, " +
                "library_allowance = ?, " +
                "child_allowance = ?, " +
                "spouse_allowance = ?, " +
                "base_salary = ? " +
                "WHERE category = ? and status = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmtSelect = conn.prepareStatement(selectSql);
             PreparedStatement pstmtUpdate = conn.prepareStatement(updatesql)) {

            pstmtSelect.setString(1, category);
            pstmtSelect.setString(2, status);

            ResultSet rs = pstmtSelect.executeQuery();

            if (!rs.next()) {
                System.out.println("Δεν βρέθηκε το category = " + category + " και το status = " + status);
                return;
            }

            double oldyears = rs.getDouble("years_of_service");
            double oldresearch = rs.getDouble("research_allowance");
            double oldlibrary = rs.getDouble("library_allowance");
            double oldchild = rs.getDouble("child_allowance");
            double oldspouse = rs.getDouble("spouse_allowance");
            double oldsalary = rs.getDouble("base_salary");


            double final_years = oldyears;
            double final_research = oldresearch;
            double final_library = oldlibrary;
            double final_child = oldchild;
            double final_spouse = oldspouse;
            double final_salary = oldsalary;

            System.out.println("Child = "+oldchild+"Spouse"+oldspouse);
            System.out.println("Child = "+newchild_allowance+"Spouse"+newspouse_allowance);

            if ((newchild_allowance - oldchild) < 0 || (newspouse_allowance - oldspouse) < 0) {
                System.out.println("Σφάλμα: Λάθος είσοδος (μείωση) παιδί|σύζυγος");
                return;
            }
            final_child = newchild_allowance;
            final_spouse = newspouse_allowance;

            if (category.equals("Teaching") && status.equals("Perm")) {
                if (((newresearch_allowance-oldresearch) < 0) || ((newyears_of_service-oldyears) < 0) ||
                        ((newbase_salary-oldsalary) < 0)) {
                    System.out.println("Σφάλμα: Λάθος είσοδος έρευνα|μισθός|υπηρεσία");
                    return;
                }
                final_research = newresearch_allowance;
                final_salary = newbase_salary;
                final_years = newyears_of_service;

            } else if (category.equals("Teaching") && status.equals("Contract")) {
                if ((newlibrary_allowance-oldlibrary) < 0) {
                    System.out.println("Σφάλμα: Λάθος είσοδος βιβλιοθήκη");
                    return;
                }
                final_library = newlibrary_allowance;

            } else if (category.equals("Admin") && status.equals("Perm")) {
                if (((newyears_of_service-oldyears) < 0) || ((newbase_salary-oldsalary) < 0)) {
                    System.out.println("Σφάλμα: Λάθος είσοδος μισθός|υπηρεσία");
                    return;
                }
                final_salary = newbase_salary;
                final_years = newyears_of_service;
            }

            pstmtUpdate.setDouble(1, final_years);
            pstmtUpdate.setDouble(2, final_research);
            pstmtUpdate.setDouble(3, final_library);
            pstmtUpdate.setDouble(4, final_child);
            pstmtUpdate.setDouble(5, final_spouse);
            pstmtUpdate.setDouble(6, final_salary);

            pstmtUpdate.setString(7, category);
            pstmtUpdate.setString(8, status);

            int rows = pstmtUpdate.executeUpdate();
            if (rows > 0) {
                System.out.println("Γίνεται η ανανέωση!");
            } else {
                System.out.println("Δεν έγινε η ανανέωση.");
            }

        } catch (SQLException e) {
            System.out.println("Σφάλμα στην sql: " + e.getMessage());
        }
    }
    public String[] get_salaries_benefits(String category,String status)
    {

        String sql = "SELECT * FROM Payroll_Data where category = ? and status = ?";


        String []str = new String[6];
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql))
        {
            pstmt.setString(1, category);
            pstmt.setString(2, status);

            try (ResultSet rs = pstmt.executeQuery())
            {
                if (rs.next())
                {
                    str[0] = String.valueOf(rs.getDouble("years_of_service"));
                    str[1] = String.valueOf(rs.getDouble("research_allowance"));
                    str[2] = String.valueOf(rs.getDouble("library_allowance"));
                    str[3] = String.valueOf(rs.getDouble("child_allowance"));
                    str[4] = String.valueOf(rs.getDouble("spouse_allowance"));
                    str[5] = String.valueOf(rs.getDouble("base_salary"));

                    System.out.println("Βρεθηκε το category και status");
                }
                else
                {
                    System.out.println("Δεν βρεθηκε το category και status");
                    return null;
                }
            }
        }
        catch (SQLException e)
        {
            System.out.println("Λαθος στην βαση δεδομενων" + e.getMessage());
            e.printStackTrace();
        }
        return str;
    }




    public boolean fireEmployee(int empId)
    {
        LocalDate date = LocalDate.now();
        int lastDayOfMonth = date.with(TemporalAdjusters.lastDayOfMonth()).getDayOfMonth();
        //int lastDayOfMonth = 31;//date.with(TemporalAdjusters.lastDayOfMonth()).getDayOfMonth();


        if (lastDayOfMonth != date.getDayOfMonth())
        {
            System.out.println("Σφαλμα λαθος ημερομηνια");
            return false;
        }

        System.out.println("emp_id = "+empId);
        String deleteHistorySql = "delete from Payroll_History where emp_id = ?";
        String deleteEmpSql = "delete from Employee_Data  where emp_id = ? ";


        try (Connection conn = DriverManager.getConnection(url, user, password))
        {
            try(PreparedStatement pstmtHistory = conn.prepareStatement(deleteHistorySql))
            {
                pstmtHistory.setInt(1, empId);
                pstmtHistory.executeUpdate();
            }
            try (PreparedStatement pstmtEmp = conn.prepareStatement(deleteEmpSql)) {
                pstmtEmp.setInt(1, empId);
                int rows = pstmtEmp.executeUpdate();

                if (rows > 0) {
                    System.out.println("Ο υπάλληλος απολύθηκε μαζι με το ιστορικο του.");
                    return true;
                } else {
                    System.out.println("Δεν βρεθηκε ο υπαλληλος.");
                    return false;
                }
            }
        }

        catch (SQLException e) {
            System.out.println("Σφαλμα: " + e.getMessage());
        }
        return false;
    }


    public String[][] calculateAndSavePayroll() {
        String fetchEmployeesSql = "SELECT e.emp_id, e.name, e.category, e.status, e.contract_salary, " +
                "e.hire_date, e.children_count, e.marital_status, e.bank_account, e.bank_name, " +
                "p.base_salary, p.years_of_service, p.child_allowance, " +
                "p.spouse_allowance, p.research_allowance, p.library_allowance " +
                "FROM Employee_Data e " +
                "JOIN Payroll_Data p ON e.category = p.category AND e.status = p.status";

        String insertHistorySql = "INSERT INTO Payroll_History (emp_id, worker_name, payment_date, total_amount) VALUES (?,?,?,?)";

        LocalDate payDate = LocalDate.now().with(TemporalAdjusters.lastDayOfMonth());
        List<String[]> statementList = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             PreparedStatement pstmtInsert = conn.prepareStatement(insertHistorySql);
             ResultSet rs = stmt.executeQuery(fetchEmployeesSql)) {

            while (rs.next()) {
                try {
                    int empId = rs.getInt("emp_id");
                    String name = rs.getString("name");
                    String category = rs.getString("category");
                    String status = rs.getString("status");
                    String bank_account = rs.getString("bank_account");
                    String bank_name = rs.getString("bank_name");

                    double valBase = 0, valYears = 0, valChild = 0, valSpouse = 0, valSpecial = 0, valTotal = 0;

                    if ("Contract".equalsIgnoreCase(status)) {
                        // Contract employees get a Flat Contract Salary
                        valBase = rs.getDouble("contract_salary");

                        // Contract Teachers get Library Allowance (Usually Flat)
                        if ("Teaching".equalsIgnoreCase(category)) {
                            valSpecial += rs.getDouble("library_allowance");
                        }
                    } else {
                        // Permanent employees get Base Salary + Percentages
                        valBase = rs.getDouble("base_salary");

                        // 1. YEARS OF SERVICE (Percentage of Base)
                        // Slide: "Base + 15% for every year"
                        Date hireDate = rs.getDate("hire_date");
                        int years = 0;
                        if (hireDate != null) years = payDate.getYear() - hireDate.toLocalDate().getYear();

                        double yearPct = rs.getDouble("years_of_service"); // e.g., 17.0
                        valYears = valBase * (yearPct / 100.0) * years;

                        // 2. CHILD ALLOWANCE (Percentage of Base)
                        // Slide: "+ 5% of salary for each child" (Ages don't matter)
                        int childCount = rs.getInt("children_count");
                        double childPct = rs.getDouble("child_allowance"); // e.g., 5.0
                        valChild = valBase * (childPct / 100.0) * childCount;

                        // 3. SPOUSE ALLOWANCE (Percentage of Base)
                        // Slide: "+ 5% of salary for spouse"
                        if ("Married".equalsIgnoreCase(rs.getString("marital_status"))) {
                            double spousePct = rs.getDouble("spouse_allowance"); // e.g., 5.0
                            valSpouse = valBase * (spousePct / 100.0);
                        }

                        // 4. RESEARCH ALLOWANCE (Teaching Perm)
                        // Slide: "+ Research Allowance" (Implies flat add-on)
                        if ("Teaching".equalsIgnoreCase(category)) {
                            valSpecial = rs.getDouble("research_allowance");
                        }
                    }

                    valTotal = valBase + valYears + valChild + valSpouse + valSpecial;


                    String[] row = new String[11];
                    row[0] = name;
                    row[1] = category;
                    row[2] = status;
                    row[3] = bank_account;
                    row[4] = bank_name;
                    row[5] = String.format("%.2f", valBase);
                    row[6] = String.format("%.2f", valYears);
                    row[7] = String.format("%.2f", valChild);
                    row[8] = String.format("%.2f", valSpouse);
                    row[9] = String.format("%.2f", valSpecial);
                    row[10] = String.format("%.2f €", valTotal);
                    statementList.add(row);

                    pstmtInsert.setInt(1, empId);
                    pstmtInsert.setString(2, name);
                    pstmtInsert.setDate(3, Date.valueOf(payDate));
                    pstmtInsert.setDouble(4, valTotal);
                    pstmtInsert.executeUpdate();

                } catch (SQLException e) {
                    System.out.println("Error paying employee " + rs.getString("name") + ": " + e.getMessage());
                }
            }
        } catch (SQLException e) {
            System.out.println("Global SQL Error: " + e.getMessage());
            e.printStackTrace();
        }

        String[][] resultMatrix = new String[statementList.size()][11];
        for (int i = 0; i < statementList.size(); i++) {
            resultMatrix[i] = statementList.get(i);
        }
        return resultMatrix;
    }




    public String[][] getPayrollStatusByCategory() {
        String sql = "SELECT e.emp_id, e.category, e.status, p.worker_name, p.total_amount " +
                "FROM Payroll_History p " +
                "JOIN Employee_Data e ON p.emp_id = e.emp_id " +
                "ORDER BY e.category, e.status";

        List<String[]> list = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                String id = String.valueOf(rs.getInt("emp_id"));
                String category = rs.getString("category");
                String status = rs.getString("status");
                String name = rs.getString("worker_name");
                String amount = String.format("%.2f €", rs.getDouble("total_amount"));

                String[] row = {id, category, status, name, amount};
                list.add(row);
            }
        } catch (SQLException e) {
            System.out.println("Σφάλμα: " + e.getMessage());
            return new String[0][0];
        }

        String[][] result = new String[list.size()][5];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }
        return result;
    }


    public String[][] getSalaryStats() {
        String sql = "SELECT e.category, e.status, " +
                "MAX(p.total_amount) as max_sal, " +
                "MIN(p.total_amount) as min_sal, " +
                "AVG(p.total_amount) as avg_sal " +
                "FROM Payroll_History p " +
                "JOIN Employee_Data e ON p.emp_id = e.emp_id " +
                "GROUP BY e.category, e.status";

        List<String[]> list = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                String category = rs.getString("category");
                String status = rs.getString("status");
                String max = String.format("%.2f €", rs.getDouble("max_sal"));
                String min = String.format("%.2f €", rs.getDouble("min_sal"));
                String avg = String.format("%.2f €", rs.getDouble("avg_sal"));

                String[] row = {category, status, max, min, avg};
                list.add(row);
            }
        } catch (SQLException e) {
            System.out.println("Σφάλμα Stats: " + e.getMessage());
            return new String[0][0];
        }

        String[][] result = new String[list.size()][5];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }
        return result;
    }

    public void getAverageSalaryTrend(String startDate, String endDate) {
        String sql = "SELECT payment_date, AVG(total_amount) as monthly_avg " +
                "FROM Payroll_Payment_Data " +
                "WHERE payment_date BETWEEN ? AND ? " +
                "GROUP BY payment_date " +
                "ORDER BY payment_date";

        System.out.println("\n--- Εξέλιξη Μέσου Μισθού (" + startDate + " έως " + endDate + ") ---");

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, startDate);
            pstmt.setString(2, endDate);
            ResultSet rs = pstmt.executeQuery();

            while (rs.next()) {
                System.out.printf("Ημ/νία: %s  ->  Μέσος Μισθός: %.2f€\n",
                        rs.getDate("payment_date"),
                        rs.getDouble("monthly_avg"));
            }

        } catch (SQLException e) {
            System.out.println("Σφάλμα: " + e.getMessage());
        }
    }


    public String[][] getSpecificEmployeeHistory(int empId) {

        String sql = "SELECT e.emp_id, e.name, e.category, e.status, p.payment_date, p.total_amount " +
                "FROM Employee_Data e " +
                "JOIN Payroll_History p ON e.emp_id = p.emp_id " +
                "WHERE e.emp_id = ? " +
                "ORDER BY p.payment_date DESC";

        List<String[]> list = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setInt(1, empId);
            ResultSet rs = pstmt.executeQuery();

            while (rs.next()) {
                String id = String.valueOf(rs.getInt("emp_id"));
                String name = rs.getString("name");
                String category = rs.getString("category");
                String status = rs.getString("status");
                String date = rs.getDate("payment_date").toString();
                String amount = String.format("%.2f €", rs.getDouble("total_amount"));

                String[] row = {id, name, category, status, date, amount};
                list.add(row);
            }
        } catch (SQLException e) {
            System.out.println("Σφάλμα History: " + e.getMessage());
            return new String[0][0];
        }

        String[][] result = new String[list.size()][6];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }
        return result;
    }

    public String[][] getTotalCostByCategory() {
        String sql = "SELECT e.category, e.status, SUM(p.total_amount) as total_sum " +
                "FROM Employee_Data e " +
                "JOIN Payroll_History p ON e.emp_id = p.emp_id " +
                "GROUP BY e.category, e.status";

        List<String[]> list = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                String category = rs.getString("category");
                String status = rs.getString("status");
                String total = String.format("%.2f €", rs.getDouble("total_sum"));

                String[] row = {category, status, total};
                list.add(row);
            }
        } catch (SQLException e) {
            System.out.println("Σφάλμα Costs: " + e.getMessage());
            return new String[0][0];
        }

        String[][] result = new String[list.size()][3];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }
        return result;
    }


    public String[][] getAverageSalaryTrends() {
        String sql = "SELECT payment_date, AVG(total_amount) as avg_pay " +
                "FROM Payroll_History " +
                "GROUP BY payment_date " +
                "ORDER BY payment_date";

        List<String[]> list = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                String date = rs.getDate("payment_date").toString();
                String avg = String.format("%.2f €", rs.getDouble("avg_pay"));

                String[] row = {date, avg};
                list.add(row);
            }
        } catch (SQLException e) {
            System.out.println("Σφάλμα Trends: " + e.getMessage());
            return new String[0][0];
        }

        String[][] result = new String[list.size()][2];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }
        return result;
    }



}
