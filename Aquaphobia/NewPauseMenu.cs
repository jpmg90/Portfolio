using UnityEngine;
using System.Collections;

public class NewPauseMenu : MonoBehaviour 
{
    public GUISkin skin;
	public GUIStyle myStyle;
	public GUIStyle TextStyle;
		
	public float height;
	public float width;
		
	float soundVolume;
	float musicVolume;
	HUDVisibility hudVisibility;
	
    private float gldepth = -0.5f;
    private float startTime = 0.1f;
    
    private float savedTimeScale;
    
    public GameObject start;
    
    public string url = "unity.html";
    
    public Color statColor = Color.white;
    
    public enum Page
	{
        None,Main,Options,Quit,
    }
    
    private Page currentPage;
    
    private int toolbarInt = 0;
    private string[]  toolbarstrings =  {"Audio","Graphics", "System"};
    
    void Start() 
	{
        Time.timeScale = 1;
        //PauseGame();
		
		soundVolume = Preferences.Instance.SoundVolume;
		musicVolume = Preferences.Instance.MusicVolume;
		hudVisibility = Preferences.Instance.hudVisibility;
    }
	// Update is called once per frame
	void Update () 
	{
		if(musicVolume != Preferences.Instance.MusicVolume)
		{
			Preferences.Instance.MusicVolume = musicVolume;
			
			MusicPlayer[] musicObjects = (MusicPlayer[])GameObject.FindObjectsOfType(typeof(MusicPlayer));
			foreach(MusicPlayer mp in musicObjects)
				mp.ChangeVolume();
		}
		
		if(soundVolume != Preferences.Instance.SoundVolume)
		{
			Preferences.Instance.SoundVolume = soundVolume;	
		}
		
		if(hudVisibility != Preferences.Instance.hudVisibility)
			Preferences.Instance.hudVisibility = hudVisibility;
	
	}
        
    static bool IsDashboard() 
	{
        return Application.platform == RuntimePlatform.OSXDashboardPlayer;
    }
    
    static bool IsBrowser() 
	{
        return (Application.platform == RuntimePlatform.WindowsWebPlayer ||
            Application.platform == RuntimePlatform.OSXWebPlayer);
    }
    
    void LateUpdate () 
	{        
        if (Input.GetKeyDown("escape")) 
        {
            switch (currentPage) 
            {
                case Page.None: 
                    PauseGame(); 
                    break;
                
                case Page.Main: 
                    if (!IsBeginning()) 
                        UnPauseGame(); 
                    break;
				
                default: 
                    currentPage = Page.Main;
                    break;
            }
        }
    }
    
    void OnGUI () 
	{
        if (skin != null) 
		{
            GUI.skin = skin;
        }
        //ShowStatNums();
        if (IsGamePaused()) 
		{
            GUI.color = statColor;
            switch (currentPage) 
			{
			case Page.Main: MainPauseMenu(); break;
			case Page.Options: ShowToolbar(); break;
			case Page.Quit: ShowQuit(); break;
            }
        }   
    }
    
	void DisableInput()
	{
		
	}
	
    void ShowToolbar() 
	{
        BeginPage(width+275,height+50);
        toolbarInt = GUILayout.Toolbar (toolbarInt, toolbarstrings,myStyle);
        switch (toolbarInt)
		{
            case 0: VolumeControl(); break;
            case 1: Qualities(); QualityControl(); HUDOptions(); break;
            case 2: ShowDevice(); break;
        }
        EndPage();
    }
    void HUDOptions()
	{
		GUILayout.Label("HUD Visibility: " + hudVisibility.ToString(), TextStyle);
		GUILayout.BeginHorizontal();
		if(GUILayout.Button("<-", myStyle))
		{
			hudVisibility--;
			
			if(hudVisibility < (HUDVisibility)0)
				hudVisibility = (HUDVisibility)2;				
		}
		if(GUILayout.Button("->", myStyle))
		{
			hudVisibility++;
			
			if(hudVisibility > (HUDVisibility)2)
				hudVisibility = (HUDVisibility)0;
		}
        GUILayout.EndHorizontal();
	}
    void ShowQuit()
	{
		if(gameObject.GetComponent(typeof(ConfirmationWindowScript)) == null)
		{
			// Create a confirmationScript
			ConfirmationWindowScript confirmationWindow = gameObject.AddComponent<ConfirmationWindowScript>();
			// Set Description of the confirmation window
			confirmationWindow.description = "Are you sure you wish to quit?";
			// Set Width and Height
			confirmationWindow.SetWidthAndHeight(70,35);
			// Set the OnConfirm to load the main menu
			confirmationWindow.OnConfirm += () => Application.LoadLevel("Main Menu");
		}
		currentPage = Page.None;
	}
    void ShowBackButton() 
	{
        if (GUI.Button(new Rect(20, Screen.height - 50, 100, 30),"Back",myStyle))
		{
            currentPage = Page.Main;
        }
    }
    
    void ShowDevice() 
	{
        GUILayout.Label("Unity player version "+Application.unityVersion, TextStyle);
        GUILayout.Label("Graphics: "+SystemInfo.graphicsDeviceName+" "+
        SystemInfo.graphicsMemorySize+"MB\n"+
        SystemInfo.graphicsDeviceVersion+"\n"+
        SystemInfo.graphicsDeviceVendor, TextStyle);
        GUILayout.Label("Shadows: "+SystemInfo.supportsShadows, TextStyle);
        GUILayout.Label("Image Effects: "+SystemInfo.supportsImageEffects, TextStyle);
        GUILayout.Label("Render Textures: "+SystemInfo.supportsRenderTextures, TextStyle);
    }
    
    void Qualities() 
	{
        switch (QualitySettings.currentLevel) 
        {
            case QualityLevel.Fastest:
                GUILayout.Label("Graphics Quality: Fastest", TextStyle);
                break;
            case QualityLevel.Fast:
                GUILayout.Label("Graphics Quality: Fast", TextStyle);
                break;
            case QualityLevel.Simple:
                GUILayout.Label("Graphics Quality: Simple", TextStyle);
                break;
            case QualityLevel.Good:
                GUILayout.Label("Graphics Quality: Good", TextStyle);
                break;
            case QualityLevel.Beautiful:
                GUILayout.Label("Graphics Quality: Beautiful", TextStyle);
                break;
            case QualityLevel.Fantastic:
                GUILayout.Label("Graphics Quality: Fantastic", TextStyle);
                break;
        }
    }
    
    void QualityControl()
	{
        GUILayout.BeginHorizontal();
        if (GUILayout.Button("Decrease",myStyle))
		{
            QualitySettings.DecreaseLevel();
        }
		
        if (GUILayout.Button("Increase",myStyle)) 
		{
            QualitySettings.IncreaseLevel();
        }
        GUILayout.EndHorizontal();
    }
    
    void VolumeControl() 
	{
        GUILayout.Label("Master Volume", TextStyle);
        AudioListener.volume = GUILayout.HorizontalSlider(AudioListener.volume, 0, 1);
		
		GUILayout.Label("Sound Volume", TextStyle);
		soundVolume = GUILayout.HorizontalSlider(soundVolume, 0, 1);		
		
		GUILayout.Label("Music Volume", TextStyle);
		musicVolume = GUILayout.HorizontalSlider(musicVolume, 0, 1);
    }
    
    void StatControl() 
	{
        GUILayout.BeginHorizontal();
        GUILayout.EndHorizontal();
    }
    
    bool IsBeginning()
	{
        return (Time.time < startTime);
    }
    
    
    void MainPauseMenu() 
	{		
        BeginPage(width,height);
        if (GUILayout.Button("Continue",myStyle))
		{
            UnPauseGame();    
        }
        if (GUILayout.Button ("Options",myStyle))
		{
            currentPage = Page.Options;
        }
        if (GUILayout.Button ("Quit Game",myStyle))
		{
            currentPage = Page.Quit;
        }
        if (IsBrowser() && !IsBeginning() && GUILayout.Button ("Restart")) 
		{
            Application.OpenURL(url);
        }
        EndPage();
    }
    
    void GetObjectStats()
	{
        GameObject[] ob = FindObjectsOfType(typeof(GameObject)) as GameObject[];
        foreach (GameObject obj in ob) 
		{
            GetObjectStats(obj);
        }
    }
    
    void GetObjectStats(GameObject obj)
	{
        Component[] filters;
        filters = obj.GetComponentsInChildren<MeshFilter>();
        foreach( MeshFilter f  in filters )
        {
        }
    }
    
    void PauseGame() 
	{
        savedTimeScale = Time.timeScale;
        Time.timeScale = 0;
        AudioListener.pause = true;
        currentPage = Page.Main;
    }
    
    void UnPauseGame() 
	{
        Time.timeScale = savedTimeScale;
        AudioListener.pause = false;
		
        currentPage = Page.None;
        
        if (IsBeginning() && start != null) 
		{
            start.active = true;
        }
    }
    
    bool IsGamePaused()
	{
        return (Time.timeScale == 0);
    }
    
    void OnApplicationPause(bool pause)
	{
        if (IsGamePaused())
		{
            AudioListener.pause = true;
        }
    } 
    void BeginPage(float width, float height)
	{
		//GUI.matrix = Matrix4x4.TRS(new Vector3((Screen.width/2)*GUIsF.x, (Screen.height/2)*GUIsF.y,0), Quaternion.identity, GUIsF);
       GUILayout.BeginArea( new Rect((Screen.width - width) / 2, (Screen.height - height) / 2, width, height));
    }
    
    void EndPage()
	{
        GUILayout.EndArea();
        if (currentPage != Page.Main) 
		{
            ShowBackButton();
        }
    }
	
}
