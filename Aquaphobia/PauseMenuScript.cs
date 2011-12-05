using UnityEngine;
using System.Collections;

public class PauseMenuScript : MonoBehaviour
{	
	const float gameTimeScale = 1;
	bool showGUI;
	
	// Use this for initialization
	void Start () 
	{
		// Pause the game when the window opens
		Time.timeScale = 0;
	}
	
	void Update()
	{
		// If Escaped is pressed then destroy the menu
		if(Input.GetKeyDown(KeyCode.Escape))
			Destroy(this);
		
		if(!showGUI)
		{
			if(GetComponent<OptionsMenuScript>() == null)
				showGUI = true;
		}
	}
	
	void OnGUI()
	{
		// Height and width of the buttons that are going to be created
		const float width = 150;
		const float height = 30;
		
		if(showGUI)
		{
			float x = Screen.width / 2 - 50;		
			float y = Screen.height / 2;
			
			// Return button, Destroys the menu
			if(GUI.Button(new Rect(x, y, width, height), "Return"))
				Destroy(this);
			
			y += 40;
			// Options Button
			if(GUI.Button(new Rect(x, y, width, height), "Options"))
			{
				//display Options
				gameObject.AddComponent<OptionsMenuScript>();
				showGUI = false;
			}
			
			y += 40;
			// Quit Button
			if(GUI.Button(new Rect(x, y, width, height), "Quit to Main Menu"))
			{
				if(gameObject.GetComponent(typeof(ConfirmationWindowScript)) == null)
				{
					// Create a confirmationScript
					ConfirmationWindowScript confirmationWindow = gameObject.AddComponent<ConfirmationWindowScript>();
					// Set Description of the confirmation window
					confirmationWindow.description = "Are you sure you wish to quit?";
					// Set the OnConfirm to load the main menu
					confirmationWindow.OnConfirm += () => Application.LoadLevel("Main Menu");
				}
				Destroy(this);
			}
		}
	}
	
	// ON Destroy
	void OnDestroy()
	{
		// Reset Time
		if(gameObject.GetComponent(typeof(ConfirmationWindowScript)) == null)
		{
			Time.timeScale = gameTimeScale;
		}
	}
}
