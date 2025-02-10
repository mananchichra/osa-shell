import java.util.ArrayList;
import java.util.List;

class UserAccount {
    private String username;
    private String password;
    private String email;
    private String phone;
    private boolean isLoggedIn;
    private List<String> activityLog;

    public UserAccount(String username, String password, String email, String phone) {
        this.username = username;
        this.password = password;
        this.email = email;
        this.phone = phone;
        this.isLoggedIn = false;
        this.activityLog = new ArrayList<>();
    }

    public void authenticate(String inputUsername, String inputPassword) {
        if (inputUsername.equals(username) && inputPassword.equals(password)) {
            isLoggedIn = true;
            System.out.println("Login successful.");
            activityLog.add("User logged in.");
            sendLoginNotification();
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private void sendLoginNotification() {
        System.out.println("Sending login notification to " + email + " and " + phone);
    }

    public void updateContactInfo(String newEmail, String newPhone) {
        this.email = newEmail;
        this.phone = newPhone;
        activityLog.add("Updated contact information.");
    }

    public void printActivityLog() {
        System.out.println("Activity log for " + username + ":");
        for (String log : activityLog) {
            System.out.println("- " + log);
        }
    }
}
