# EcoLight_Maestro

**EcoLight Maestro focuses on smart control of LED streetlights, ensuring they operate automatically using preset time slots and real-time ambient light detection.**

---

## Project Overview
EcoLight Maestro is a **smart energy management system** designed using the **ARM7TDMI-S (LPC2148) microcontroller**.  
The project automatically controls street lights based on environmental conditions, optimizing energy usage and reducing wastage.  
It demonstrates the real-time working of embedded systems for **sustainable smart living**.

---

## Features
- Automatic switching of lights based on ambient light.  
- **Real-Time Clock (RTC)** integration for scheduled control.  
- Energy-efficient design using **ARM7-based microcontroller**.  
- **LCD Display** for system status & monitoring.  
- User-friendly configuration and easy expandability.

---

## Block Diagram
<img width="849" height="467" alt="Screenshot 2025-12-06 202153" src="https://github.com/user-attachments/assets/551055a8-6466-4454-a34d-5968f93e44ee" />


---

## Technical Specifications

### Hardware
- LPC2148 Microcontroller  
- Light Dependent Resistor (LDR)  
- LEDs (Street Lights)  
- 16x2 LCD Display  
- Switch  
- Keypad Matrix (4x4)  

### Software
- Embedded C (Keil µVision)  
- Flash Magic (for programming LPC2148)  
- Proteus (for simulation)  

---

## System Workflow
1. **Startup** → Initialize LCD, RTC, ADC, LEDs, Relay.  
2. **RTC Check** → If current time matches schedule → Light ON.  
3. **Else** → LDR sensor checks ambient brightness:  
   - Dark → Light ON  
   - Bright → Light OFF  
4. **LCD Display** → Shows RTC time + Light status (ON/OFF).  
5. **User Mode** → Press switch → Update RTC / Modify schedules via keypad.  

---

## Simulation Circuit & Results
### Simulation Circuit
<img width="1043" height="736" alt="Screenshot 2025-12-06 212427" src="https://github.com/user-attachments/assets/b588ffcc-4e74-42ca-a1cb-a4b96152f959" />


### Simulation Results
<img width="1045" height="732" alt="Screenshot 2025-12-06 212503" src="https://github.com/user-attachments/assets/1a6db922-8370-45f7-b38c-1926afa00d09" />

 
<img width="1045" height="733" alt="Screenshot 2025-12-06 212542" src="https://github.com/user-attachments/assets/35a46c31-6e73-47df-94f5-8ceda66fdf39" />


<img width="1055" height="735" alt="Screenshot 2025-12-06 212625" src="https://github.com/user-attachments/assets/e518142c-68d0-4b2b-a55e-13addddc6faf" />

---


## 7. Keil Code Screenshot / Description
![WhatsApp Image 2025-12-06 at 21 53 55_e9a48d54](https://github.com/user-attachments/assets/f78cdda5-dc08-4200-963b-a917c730666f)


## 8. Hardware Setup
![WhatsApp Image 2025-12-06 at 21 55 18_5f7430e0](https://github.com/user-attachments/assets/43f3c409-7b95-4715-aed4-478faaabb372)


---

## 9. Notes / Important Points
- RTC must be **accurate** for proper scheduling.  
- LDR threshold can be **calibrated** based on local lighting conditions.  
- User can **manually update time or schedules** via keypad.

---

## 10. Improvisation / Future Scope
- Integrate **wireless control** via IoT to monitor streetlights remotely.  
- Add **motion detection** for adaptive lighting in empty streets.  
- Implement **energy logging** to analyze consumption trends.  
- Replace LEDs with **solar-powered lights** for fully sustainable operation.  
- Enhance **LCD interface** with graphical display and user-friendly menus.

---

## 11. Limitations
- RTC dependency: Incorrect RTC time may cause improper light operation.  
- LDR sensitivity may vary under extreme weather conditions.  
- Limited scalability: Current design is for small-scale deployment; may need hardware modifications for large streets.  
- Manual configuration required for threshold and schedules.  

---

## 12. Authors
- **Surya Prakash Vadaparthi**  
- [Optional: Add team members if applicable]  

---

## 13. Conclusion / Learning Outcome
This project demonstrates **energy-efficient, automated street lighting** using embedded systems.  
It is useful for **smart city applications**, reducing energy wastage, and provides **hands-on experience** with microcontroller-based real-time systems.

---



