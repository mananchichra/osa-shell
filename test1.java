import java.util.ArrayList;
import java.util.List;

// **God Object**: Manages user details, authentication, logging, and notifications.
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

    // **Long Method**: Doing too many things in one method.
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

    // **Feature Envy**: This method should belong to a Notification class.
    private void sendLoginNotification() {
        System.out.println("Sending login notification to " + email + " and " + phone);
    }

    // **Primitive Obsession**: Using strings for username, email, and phone instead of proper objects.
    public void updateContactInfo(String newEmail, String newPhone) {
        this.email = newEmail;
        this.phone = newPhone;
        activityLog.add("Updated contact information.");
    }

    // **Divergent Change**: If user tracking changes, multiple methods (`authenticate`, `updateContactInfo`) need modification.
    public void printActivityLog() {
        System.out.println("Activity log for " + username + ":");
        for (String log : activityLog) {
            System.out.println("- " + log);
        }
    }
}
