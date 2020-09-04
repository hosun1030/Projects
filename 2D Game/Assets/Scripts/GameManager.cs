using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager instance;

    public Vector2 playerInitialPosition;

    private GameObject[] enemies;
    private GameObject player;


   void Awake()
    {
        if (instance == null)
            instance = this;
        Time.timeScale = 1f;
    }
    
    
    void Start()
    {
        enemies = GameObject.FindGameObjectsWithTag("Enemy");
        player = GameObject.FindWithTag("Player");
    }

    public void PlayerReachedGoal()
    {

        UnityEngine.SceneManagement.SceneManager.LoadScene(
        UnityEngine.SceneManagement.SceneManager.GetActiveScene().buildIndex + 1);
    }
    public void PlayerDied() {
        Time.timeScale = 0f;

        StartCoroutine(RestartLevel());
    }
    IEnumerator RestartLevel()
    {
        yield return new WaitForSecondsRealtime(1f);

        UnityEngine.SceneManagement.SceneManager.LoadScene(
        UnityEngine.SceneManagement.SceneManager.GetActiveScene().name);

    }
}
