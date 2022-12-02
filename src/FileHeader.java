public class FileHeader {
    private final byte[] signature = new byte[2];
    private final byte[] fileSize = new byte[4];
    private final byte[] reserved1 = new byte[2];
    private final byte[] reserved2 = new byte[2];
    private final byte[] dataOfset = new byte[4];

    private byte[] getSignature() {
        return signature;
    }

    private byte[] getFileSize() {
        return fileSize;
    }

    private byte[] getReserved1() {
        return reserved1;
    }

    private byte[] getReserved2() {
        return reserved2;
    }

    private byte[] getDataOfset() {
        return dataOfset;
    }

    private void setSignature(byte[] bytes) {
        for (int i = 0; i < signature.length; i++) {
            if (i < bytes.length)
                signature[i] = bytes[i];
            else
                signature[i] = 0;
        }

    }

    private void setFileSize(byte[] bytes) {
        for (int i = 0; i < fileSize.length; i++) {
            if (i < bytes.length)
                fileSize[i] = bytes[i];
            else
                fileSize[i] = 0;
        }
    }

    private void setReserved1(byte[] bytes) {
        for (int i = 0; i < reserved1.length; i++) {
            if (i < bytes.length)
                reserved1[i] = bytes[i];
            else
                reserved1[i] = 0;
        }
    }

    private void setReserved2(byte[] bytes) {
        for (int i = 0; i < reserved2.length; i++) {
            if (i < bytes.length)
                reserved2[i] = bytes[i];
            else
                reserved2[i] = 0;
        }
    }

    private void setDataOfset(byte[] bytes) {
        for (int i = 0; i < dataOfset.length; i++) {
            if (i < bytes.length)
                dataOfset[i] = bytes[i];
            else
                dataOfset[i] = 0;
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null)
            return false;
        if (obj.getClass() != getClass())
            return false;
        FileHeader other = (FileHeader) obj;
        if (!(other.signature.equals(signature) && other.fileSize.equals(fileSize)
                && other.reserved1.equals(reserved1) && other.reserved2.equals(reserved2)
                && other.dataOfset.equals(dataOfset)))
            return false;
        return true;
    }

    @Override
    public String toString() {// TODO
        return signature.toString() + fileSize.toString() + reserved1.toString() + reserved2.toString() + dataOfset.toString();
    }

}
