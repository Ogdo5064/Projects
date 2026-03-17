import java.sql.*;

public class DatabaseManager {
    private final String url = "jdbc:mysql://localhost:3306/uoc_payroll?allowPublicKeyRetrieval=true&useSSL=false";
    private final String user = "root";
    private final String password = "Csmajor";

    public String get_url() { return url; }
    public String get_user() { return user; }
    public String get_password() { return password; }

    public DatabaseManager() {
        createTable();
    }

    public void createTable() {

        try (Connection conn = DriverManager.getConnection(get_url(), get_user(), get_password());
             Statement stmt = conn.createStatement()) {

            stmt.executeUpdate("CREATE DATABASE IF NOT EXISTS uoc_payroll");

            String Employee_Data = "CREATE TABLE IF NOT EXISTS Employee_Data (" +
                    "emp_id int auto_increment primary key," +
                    "name varchar(255)," +
                    "marital_status varchar(20)," +
                    "children_count int," +
                    "children_ages varchar(255)," +
                    "category varchar(20)," +
                    "status varchar(20)," +
                    "department varchar(100)," +
                    "hire_date date," +
                    "contract_date date," +
                    "address varchar(255)," +
                    "phone varchar(20)," +
                    "bank_account varchar(50)," +
                    "bank_name varchar(100)," +
                    "contract_salary decimal(10,2) default 0)";

            stmt.executeUpdate(Employee_Data);
            System.out.println(" Ο πίνακας Employee_Data ελέγχθηκε/δημιουργήθηκε!");


            String Payroll_Data = "CREATE TABLE IF NOT EXISTS Payroll_Data (" +
                    "category varchar(20) not null," +
                    "status varchar(20) not null," +
                    "years_of_service decimal(10, 2)," +
                    "research_allowance decimal(10,2)," +
                    "library_allowance decimal(10,2)," +
                    "child_allowance decimal(10,2)," +
                    "spouse_allowance decimal(10,2)," +
                    "base_salary decimal(10,2)," +
                    "unique(category, status)" +
                    ")";
            stmt.executeUpdate(Payroll_Data);
            String insertsql = "INSERT IGNORE INTO Payroll_Data " +
                    "(category, status, years_of_service, research_allowance, library_allowance, child_allowance, spouse_allowance, base_salary) VALUES " +
                    "('Admin', 'Perm', 10.00, 0.00, 0.00, 50.00, 40.00, 1000.00), " +
                    "('Teaching', 'Perm', 10.00, 300.00, 0.00, 50.00, 40.00, 1400.00), " +
                    "('Admin', 'Contract', 0.00, 0.00, 0.00, 0.00, 0.00, 0.00), " +
                    "('Teaching', 'Contract', 0.00, 0.00, 150.00, 0.00, 0.00, 0.00)";
            stmt.executeUpdate(insertsql);
            System.out.println("Ο πίνακας Payroll_Data ελέγχθηκε/δημιουργήθηκε!");


            String Payroll_History = "CREATE TABLE IF NOT EXISTS Payroll_History (" +
                    "payment_id int auto_increment primary key," +
                    "emp_id int," +
                    "worker_name varchar(255)," +
                    "payment_date date," +
                    "total_amount decimal(10,2)," +
                    "FOREIGN KEY (emp_id) REFERENCES Employee_Data(emp_id) ON DELETE SET NULL" +
                    ")";
            stmt.executeUpdate(Payroll_History);
            System.out.println("Ο πίνακας Payroll_History ελέγχθηκε/δημιουργήθηκε!");

            System.out.println("Η αρχικοποίηση της βάσης ολοκληρώθηκε.");

        } catch (Exception e) {
            System.out.println("Σφαλμα στο database");
            e.printStackTrace();
        }
    }

}