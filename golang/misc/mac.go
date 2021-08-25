
package main

import (
    "crypto/rand"
    "fmt"
)

// For this function please see https://stackoverflow.com/questions/21018729/generate-mac-address-in-go
func GenerateMacAddr() string {
    const MAC_ADDR_LEN = 6

    byteBuffer := make([]byte, MAC_ADDR_LEN)
    _, err := rand.Read(byteBuffer)
    if err != nil {
        return ""
    }
    // Set this to avoid conflict with global addr & ensure it is a unicast addr
    byteBuffer[0] = (byteBuffer[0] | 2) & 0xfe

    macAddr := fmt.Sprintf("%02x:%02x:%02x:%02x:%02x:%02x", byteBuffer[0], byteBuffer[1], 
        byteBuffer[2], byteBuffer[3], byteBuffer[4], byteBuffer[5])

    return macAddr
}

func isStringValInArray(haystack []string, needle string) bool {
    for _, value := range haystack {
        if needle == value {
            return true
        }
    }
    return false
}

func GenerateMultipleMacAddr(numberOfAddr int) ([]string, error) {
    var macAddrArray []string

    i := 0
    for i < numberOfAddr {
        macAddr := GenerateMacAddr()
        if macAddr == "" {
            return nil, fmt.Errorf("Failed to generate a valid MAC address")
        }

        if isStringValInArray(macAddrArray, macAddr) {
            // it means we have generated a duplicate address
            // hence we need to generate another without incrementing the counter
            continue
        }

        macAddrArray = append(macAddrArray, macAddr)
        i++
    }
    
    return macAddrArray, nil
}


func main() {

    noOfAddr := 20
    macAddrArray, _ := GenerateMultipleMacAddr(noOfAddr)
    
    for i:=0; i< noOfAddr; i++ {
        fmt.Printf("%s\n", macAddrArray[i])
    }
    
    return
}
