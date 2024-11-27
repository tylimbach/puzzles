Console.WriteLine("Hi");

public class BrowserHistory {
	private List<string> pages;
	private int finalPage;
	private int currentPage;
	

    public BrowserHistory(string homepage) {
		pages = [homepage];
		finalPage = 0;
		currentPage = 0;
    }
    
    public void Visit(string url) {
		currentPage++;
		if (currentPage >= pages.Count) {
			pages.Add(url);
		} else {
			pages[currentPage] = url;
		}

		finalPage = currentPage;
    }
    
    public string Back(int steps) {
		currentPage = Math.Max(currentPage - steps, 0);
		return pages[currentPage];
    }
    
    public string Forward(int steps) {
		currentPage = Math.Min(currentPage + steps, finalPage);
        return pages[currentPage];
    }
};
