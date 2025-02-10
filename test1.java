import java.util.ArrayList;
import java.util.List;

class Employee {
    private String name;
    private String department;
    private double salary;
    private List<String> tasks;

    public Employee(String name, String department, double salary) {
        this.name = name;
        this.department = department;
        this.salary = salary;
        this.tasks = new ArrayList<>();
    }

    public void addTask(String task) {
        tasks.add(task);
    }

    public void removeTask(String task) {
        tasks.remove(task);
    }

    public List<String> getTasks() {
        return tasks;
    }

    public double calculateAnnualSalary() {
        return salary * 12;
    }

    public double calculateTax() {
        return calculateAnnualSalary() * 0.2;
    }

    public double calculateBonus() {
        return salary * 0.1;
    }

    public double calculateNetSalary() {
        return calculateAnnualSalary() - calculateTax() + calculateBonus();
    }

    public void printSalarySlip() {
        System.out.println("Name: " + name);
        System.out.println("Department: " + department);
        System.out.println("Annual Salary: " + calculateAnnualSalary());
        System.out.println("Tax: " + calculateTax());
        System.out.println("Bonus: " + calculateBonus());
        System.out.println("Net Salary: " + calculateNetSalary());
    }
}
