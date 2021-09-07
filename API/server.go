package main

import (
    "fmt"
    "log"
    "net/http"
	"encoding/json"
	"io/ioutil"
	"os/exec"
	"strconv"
)

func homePage(w http.ResponseWriter, r *http.Request){
    fmt.Fprintf(w, "Welcome to the HomePage!")
    fmt.Println("Endpoint Hit: homePage")
}

func ram(w http.ResponseWriter, r *http.Request){
	//file, err := os.Open("/modulos/ram_p")

    bytesLeidos, err := ioutil.ReadFile("/proc/ram_p1")
	if err != nil {
		fmt.Printf("Error leyendo archivo: %v", err)
	}

	/*contenido := string(bytesLeidos)
	fmt.Println(contenido)

	var d string
	json.Unmarshal([]byte(contenido), &d)
	fmt.Println(d)*/


	var result map[string]interface{}
    json.Unmarshal([]byte(bytesLeidos), &result)

    //fmt.Println(result["users"])

	fmt.Println("Endpoint Hit: return ram")
	json.NewEncoder(w).Encode(result)
	//json.NewEncoder(w).Encode("{articulo: 'llego ram'}")
}

type Hijo struct {
    Pid   		int
    Nombre   	string
}

type Procesos struct {
    Pid   		int
    Nombre   	string
    Estado  	int    
    Uso    		int    
    Total    	int
    Mem    		int
	Usuario 	string
	Hijo		[]Hijo
}

type Datos struct {
    Total   	int
    Ejecucion   int
    Suspendido  int    
    Detenido    int    
    Zombie    	int
}

type General struct {
    Procesos 	[]Procesos
	Datos 		Datos
}


func procesos(w http.ResponseWriter, r *http.Request){
	bytesLeidos, err := ioutil.ReadFile("/proc/cpu_p1")
	if err != nil {
		fmt.Printf("Error leyendo archivo: %v", err)
	}

	var result General
    json.Unmarshal([]byte(bytesLeidos), &result)

	/*contenido := string(bytesLeidos)
	fmt.Println(contenido)*/

	fmt.Println("Endpoint Hit: return procesos")
	//json.NewEncoder(w).Encode(contenido)
	json.NewEncoder(w).Encode(result)
	//json.NewEncoder(w).Encode("{articulo: 'llego procesos'}")
}





type Data struct {
	Id           int
}

type Send struct {
	Result         bool
	Id         int
}

func kill(w http.ResponseWriter, r *http.Request) {
	var d Data
	if json.NewDecoder(r.Body).Decode(&d) != nil {
		//println("CLIENTE: error 3")
	} else {
		//firefox id 10845 / ps -ef | grep firefox
		i := strconv.Itoa(d.Id)
		
		var r Send
		
		r.Result = muerterio(i);
		r.Id = d.Id;

		fmt.Println("Endpoint Hit: return kill")
		json.NewEncoder(w).Encode(r)
	}
}

func muerterio(id string) bool {
	cmd := exec.Command("kill", "-9", id)
	stdout, err := cmd.StdoutPipe()
	if  err != nil {// Obtenga el objeto de salida, puede leer el resultado de salida del objeto
		fmt.Println(err)
	}

	defer stdout.Close () // Garantía para cerrar el flujo de salida

	if err := cmd.Start(); err != nil {// Ejecutar comando
		fmt.Println(err)
	}

	opBytes, err := ioutil.ReadAll(stdout);
	if err != nil {// Leer el resultado de salida
		fmt.Println(err)
		return false
	} else {
		fmt.Println(string(opBytes))
		return true
	}
}



func handleRequests() {
	fmt.Println("Servidor escuchando en 8080")
    http.HandleFunc("/", homePage)
    http.HandleFunc("/ram", ram)
    http.HandleFunc("/cpu", procesos)
    http.HandleFunc("/kill", kill)
    log.Fatal(http.ListenAndServe(":8080", nil))
}

func main() {
    handleRequests()
}