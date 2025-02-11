package java_project.notification;

public class NotificationService {
    public void sendEmail(String recipient, String message) {
        System.out.println("Sending Email to " + recipient + ": " + message);
    }

    public void sendSMS(String recipient, String message) {
        System.out.println("Sending SMS to " + recipient + ": " + message);
    }
}