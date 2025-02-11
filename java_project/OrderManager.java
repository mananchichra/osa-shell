package java_project;

import java_project.notification.NotificationService; // Importing NotificationService from another package

class OrderManager {
    private InventoryService inventoryService;
    private NotificationService notificationService;

    public OrderManager() {
        this.inventoryService = new InventoryService();
        this.notificationService = new NotificationService();
    }

    public void processOrder(String product, int quantity, String customerEmail) {
        if (inventoryService.getStockManager().isAvailable(product, quantity)) {
            inventoryService.getStockManager().reduceStock(product, quantity);
            System.out.println("Order placed for " + quantity + " " + product);

            // Feature Envy - OrderManager overly manipulates NotificationService
            notificationService.sendEmail(customerEmail, "Your order has been confirmed!");
            notificationService.sendSMS(customerEmail, "Order placed successfully.");
        } else {
            System.out.println("Product out of stock.");
        }
    }
}
