package java_project;

class InventoryService {
    private StockManager stockManager;

    public InventoryService() {
        this.stockManager = new StockManager();
    }

    public StockManager getStockManager() {
        return stockManager;
    }
}

class StockManager {
    public boolean isAvailable(String product, int quantity) {
        System.out.println("Checking availability for " + product);
        return quantity <= 10; // Dummy logic
    }

    public void reduceStock(String product, int quantity) {
        System.out.println("Reducing stock of " + product + " by " + quantity);
    }
}
