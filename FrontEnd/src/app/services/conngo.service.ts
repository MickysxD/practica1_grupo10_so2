import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class ConngoService {
  url_sopes:any
  constructor(private http: HttpClient) { 
    this.url_sopes = "http://18.191.208.47:8080/"
  }
  
  ram(){
    return this.http.post(this.url_sopes + 'ram', {})  
  }
  procesos(){
    return this.http.post(this.url_sopes + 'cpu', {})   
  }

  kill(data:any){
    console.log(data)
    return this.http.post(this.url_sopes + 'kill', data)     
  }
}
