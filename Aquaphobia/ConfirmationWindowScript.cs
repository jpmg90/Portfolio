using UnityEngine;
using System.Collections;

public class ConfirmationWindowScript : MonoBehaviour
{
	const float gameTimeScale = 1;
	public string description = "Default Description";
	public string optionOne = "Yes";
	public string optionTwo = "No";
	
	public delegate void EventDelegate();
	public EventDelegate OnConfirm;	
	public EventDelegate OnCancel;
	
	// Use this for initialization
	void Start () 
	{
		// Pause the game when the confirmation window opens
		Time.timeScale = 0;
	}
	
	// Need to ensure you cannot 'pause' the game when escape is press while a confirmation window is open
	
	void OnGUI()
	{
		// Button height and width
		const float width = 100;
		const float height = 30;
		
		float x = Screen.width / 2 - 50;		
		float y = Screen.height / 2;
		// Display Description Label
		GUI.Label(new Rect(x, y, width, height*2), description);
		
		// Yes Button
		y += 50;
		if(GUI.Button(new Rect(x, y, width, height), optionOne))
		{
			//Run Delegate Function
			if(OnConfirm != null)
				OnConfirm();
			
			Destroy(this);
		}
		
		// No button, destroy component
		y += 40;
		if(GUI.Button(new Rect(x, y, width, height), optionTwo))
		{
			if(OnCancel != null)
				OnCancel();
			
			Destroy(this);
		}		
	}
	
	void OnDestroy()
	{
		//Return to whatever we were doing before this was opened.
		Time.timeScale = gameTimeScale;	
	}
}

